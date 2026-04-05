require 'pstore'

module ReVIEW
  module Book
    class Base
      attr_accessor :indices
    end
  end

  module HTMLBuilderOverride
    def builder_init_file
      super
      # 索引カウンタが初期化されていなければ初期化
      @book.indices ||= []
      @catalog = access_catalog
    end

    def access_catalog
      catalog = []
      if File.exist?('_RVIDX_store.pstore')
        db = PStore.new('_RVIDX_store.pstore')
        db.transaction do
          catalog = db['catalog']
        end
      else
        @book.parts.each do |part|
          catalog.push(part.name) if part.file?
          part.chapters.each do |chap|
            catalog.push(chap.name)
          end
        end
        db = PStore.new('_RVIDX_store.pstore')
        db.transaction do
          db['catalog'] = catalog
        end
      end
      catalog
    end

    def idxlabel(str)
      label = escape_comment(escape(str))
      no = format('%04d', @book.indices.size)
      @book.indices.push([label, "#{format('%03d', @catalog.index(@chapter.name.sub('.re', '')))}_#{no}"])
      %(<span id="_RVIDX_#{no}" class="rv_index_target"></span>)
    end

    def inline_idx(str)
      %(#{idxlabel(str)}#{escape(str)})
    end

    def inline_hidx(str)
      idxlabel(str)
    end

    def result
      # 無駄めだが最後のコンテンツまで繰り返し上書きすることで最終的なすべての索引を入手できる
      File.open('_RVIDX_index_raw.txt', 'w') do |f|
        @book.indices.each do |pair|
          pair[0].gsub!('&lt;&lt;&gt;&gt;', '<<>>') # 子索引
          f.puts "#{pair[0]}\t#{pair[1]}"
        end
      end
      super
    end

    def inline_bib(id)
      %(<a href="#{@book.bib_file.gsub(/\.re\Z/,
                                       ".#{@book.config['htmlext']}")}#bib-#{normalize_id(id)}">[#{id}]</a>)
    rescue KeyError
      app_error "unknown bib: #{id}"
    end

    def bibpaper_header(id, caption)
      print %(<a id="bib-#{normalize_id(id)}">)
      print %([#{id}])
      print '</a>'
      puts " #{compile_inline(caption)}"
    end

    def bibpaper(lines, id, caption)
      puts %(<h3 id="bib-#{normalize_id(id)}">[#{id}]</h3>#{split_paragraph(lines).join("\n\n")})
    end
  end

  module LATEXBuilderOverride
    def bibpaper(lines, id, caption)
      puts %(\\bibitem[#{escape(id)}]{bib:#{id}} #{split_paragraph(lines).join("\n\n")})
    end
  end

  class HTMLBuilder
    prepend HTMLBuilderOverride
  end

  class LATEXBuilder
    prepend LATEXBuilderOverride
  end
end
