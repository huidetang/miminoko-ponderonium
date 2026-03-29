= このテンプレートの使い方

この章ではこのテンプレートの使い方について説明します。

== このテンプレートを使うのに必要なもの

このテンプレートは以下のツール・サービスを使用します。

 * GitHub
 * テキストエディタ（おすすめはVisual Studio Code）
 * Docker（あれば）

Dockerを使わない場合は以下のプログラミング言語環境が必要になりますが、@<b>{非推奨}です。

 * Node.js
 ** パッケージマネージャーはpnpmを推奨
 * Ruby
 * Python
 * poppler

ビルドする際は以下の順番でコマンドを入力してください。これはEPUBと塗り足し・トンボ無しの電子書籍用PDFを生成する手順です。OSはLinuxを想定しています。

//cmd{
# Node.jsのパッケージをインストール
$ pnpm install

# SCSSのコンパイル（ここでは文庫・縦・塗り足し無し）
$ pnpm run style:a6-tate-no-bleed

# popplerのインストール
$ apt install poppler-utils

# Playwrightのインストール
$ ./node_modules/.bin/playwright install --with-deps

# Rubyのパッケージをインストール
$ bundle install

# Pythonのパッケージをインストール
$ python -m pip install anshitsu

# 画像の白黒化
$ python grayscaling.py >> .grayscaling.log

# EPUBの生成
$ REVIEW_CONFIG_FILE=config-epub-tate.yml bundle exec rake epub

# VivliostyleによるPDFの生成
$ REVIEW_CONFIG_FILE=config-ebook-tate.yml \
  REVIEW_VSCLI_USESANDBOX=true bundle exec rake vivliostyle
//}

なお、できる限りGitHubか、Dockerコンテナ上のLinuxで行うことを推奨いたします。

== このテンプレートの仕組み

このテンプレートは以下の仕組みでPDFを生成します。

//graph[shikumi][mermaid][このテンプレートの仕組み]{
%%{init:{'theme':'neutral'}}%%
graph TD
   docx[Microsoft Wordファイル] --> pandoc[Pandoc]
   md[Markdownファイル] --> pandoc
   pandoc --> review[Re:VIEW]
   re[.reファイル] --> review
   image[画像ファイル] --> review
   scss[.scssファイル] --> sass[Sass]
   sass --> css[CSS]
   css --> review
   review --> epub[EPUB]
   review --> uplatex[upLaTeX]
   epub --> vivliostyle[Vivliostyle]
   vivliostyle --> pdf[PDF]
   uplatex --> pdf
//}

なお、デフォルトではVivliostyleによるPDF生成が選択されていますが、 @<code>{jobs.yml} のコメントアウトを外すことによりupLaTeXでもPDF生成も可能になります。

== 対応ファイル形式

本文は以下のファイル形式に対応しています。

 * Re:VIEWフォーマット（.re）形式
 * Markdownファイル
 * Microsoft Wordファイル

なお、Microsoft Wordファイルで設定した書式は全てこのテンプレートの書式に上書きされますのでご注意ください。

画像ファイルは以下の形式に対応しています。

 * PNGファイル
 * GIFファイル
 * JPEGファイル

//image[sign][PNG画像]{
//}

SVGファイルは対応していません。

図表はMermaidで作成した図を入れることができます。Mermaidの図は @<code>{//graph} 命令で取り込むことができます。

印刷用PDFでは全て白黒化されます。

== 使える書式

詳しくは @<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md,Re:VIEW公式の書式についての説明} をご参照ください。

== 以下注意事項

ここから先はこのテンプレート独自の注意事項です。

=== 対応する紙のサイズ

以下の紙サイズに対応しています。

 * A4
 * B5
 * A5
 * A6（文庫サイズ）
 * 新書版（縦書きのみ）

紙のサイズは @<code>{jobs.yml} の @<code>{ENV} の @<code>{SIZE} 項目で設定できます。

=== 組み方向

縦書きと横書きに対応しています。

組み方向を変更するには、以下の2点の設定をする必要があります。

まず、 @<code>{config.yml} の @<code>{direction} という項目の設定を変更しましょう。

設定項目の値は以下の通りです。

 : @<code>{rtl}
    ページは右から左に流れます。右綴じで、日本語縦書きの本はこちらを指定してください。
 : @<code>{ltr}
    ページは左から右に流れます。左綴じで、欧文や日本語横書きの本はこちらを指定してください。

その後、 @<code>{jobs.yml} の @<code>{ENV} の @<code>{MUKI} 項目を設定しましょう。これで、組み方向が変わるはずです。

=== 対応文字種

EPUBおよびVivliostyle版は以下の文字種に対応しています。

 * ラテン文字
 * ラテン文字拡張
 * キリル文字
 * キリル文字拡張
 * ギリシャ文字
 * ひらがな
 * カタカナ
 * 漢字
 * ハングル

なお、漢字は日本の字体で表示されますのでご注意ください。

以下は世界の言葉で「こんにちは」を表示させるものです。

 : 英語
    Hello!

 : 日本語
    こんにちは！

 : 韓国語
    안녕하세요！

 : 中国語
    你好！

 : ベトナム語
    Xin chào!

 : モンゴル語
    Сайн байна уу?

 : ギリシャ語
    Γειά σου!

 : ウクライナ語
    Привіт!

 : ポーランド語
    Cześć!

=== 表紙

表紙は350dpiの画像ファイルで作ってください。

それぞれに画像サイズを提示いたします。

 : A4
    2894 × 4093 ピクセル
 : B5
    2508 × 3541 ピクセル
 : A5
    2039 × 2894 ピクセル
 : A6
    1447 × 2039 ピクセル
 : 新書版
    1557 × 2494 ピクセル

=== Word文書のスタイル

消えます。このテンプレートで設定したスタイルに変更されます。

なお、文字のサイズを変更する形で見出しを設定すると、地の文になってしまいます。

見出しはちゃんと見出しとして設定して使ってください。

=== 絵文字

一応Cicaフォントに含まれる絵文字は使える……はずです。

🍣 ← これはお寿司ですか？

なおLaTeX版では何も表示されないはずです。

=== 索引

Re:VIEWには索引という機能がありますが、このテンプレートには対応していません。

EPUBからPDFを作るというフローですが、残念ながらEPUBでは索引機能に対応していません。

LaTeXなら対応しているのですが……。

=== コードブロック

コードブロックは直前のページで改ページされ、次のページに表示されます。

なるべくキャプションを付けることをおすすめします。

=== 参考文献

参考文献の機能を使うことができます。

@<bib>{第１巻}、@<bib>{第２巻}、@<bib>{第３巻} のように指定すると表示されます。

