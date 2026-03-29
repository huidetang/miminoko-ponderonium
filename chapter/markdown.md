# Markdown文書の変換仕様

参考: [https://github.com/kmuto/pandoc2review/blob/main/markdown-format.ja.md](https://github.com/kmuto/pandoc2review/blob/main/markdown-format.ja.md)

## 基本

`config.yml`には拡張子を`.md`ではなく、`.re`で記述する。

## 段落

Markdownの段落はそのままRe:VIEWでも段落になる。

## 空行

Re:VIEW の `//blankline` を入れるには、`\` を行末とその次の行の2回記述する。

空行にする行に全角スペースを入れるという方法もある。

## 見出し

６レベルまで。

## 引用

引用はMarkdownの機能がそのまま使えるが、Re:VIEW の `//quote` は段落のみをサポートしているため、段落以外の要素 (箇条書きなど) は期待の出力にならない。

なお、引用の入れ子は使えない。

> 人生は長い、疲れたら休め。  
> 脇道を行くのも又良し。
> 
> ——エリナとプリン

## コードブロック

バッククォート３つで表記する。

詳しくは https://github.com/kmuto/pandoc2review/blob/main/markdown-format.ja.md 参照。

```typescript {caption="コードブロックの表示"}
const variable = 0;

if (variable) {
    console.log(variable);
}
```

## リスト

- 普通に使える
- 入れ子も……
  - 多分できるかもしれない
- これで良し

## 順序付きリスト

1. 順序付きリストは最初の数値を元に採番される
   2. 途中から始めるとその数から始まる
   3. こういうこと
2. `#.` でも機能する

## 定義リスト

定義リスト
:   使える

書き方は以下の通り。

```markdown {caption="Markdownでの定義リストの書き方"}
定義リスト
:   使える
```

## 水平線

使えるらしい。

---

が、めったに使わないらしい。

## 表

期待の結果にならないおそれがある。

詳しくは https://github.com/kmuto/pandoc2review/blob/main/markdown-format.ja.md 参照。

## メタデータブロック

Frontmatterは使えない。

YAMLから参照することはできなくはないかもしれない。詳しくは https://github.com/kmuto/pandoc2review/blob/main/markdown-format.ja.md 参照。

## インライン修飾

以下のものが使える。

- 斜体 `*`
- 太字 `**`
- 取り消し線 `~~`
- 上付き文字 `^`
- 下付き文字 `~`
- バッククォート

## 数式

TeX数式形式が使える。

## リンク

普通に変換される。

## 画像

キャプションがあるときには //image、ないときには //indepimage に変換される。

`images` フォルダに配置する必要があるが、パスを指定するときは省略する。

```markdown {caption="Markdownでの画像の貼り方"}
![与謝野晶子](yosano_akiko_is_always_watching_you.png)
```

width、height、scale の属性が付けられているときには、scale パラメータに変換される。

```markdown {caption="Markdownでのスケール指定しての画像の貼り方"}
![与謝野晶子](yosano_akiko_is_always_watching_you.png){scale=2}
```

前また後に文字があるときには、インライン画像と見なし、アイコンに変換される。

```markdown {caption="Markdownでのインライン画像の貼り方"}
レターパックで ![与謝野晶子](yosano_akiko_is_always_watching_you.png) 送れ
```

レターパックで ![与謝野晶子](yosano_akiko_is_always_watching_you.png) 送れ

## Div と Span

HTML の生タグであるブロック `<div>`、インライン `<span>` の属性情報を使って Re:VIEW の命令に変換できる。

縦中横はspanタグを使える。

```markdown {caption="MarkdownでのHTMLタグの使用"}
万物のすべての答えは<span class="tcy">42</span>である。
```

万物のすべての答えは<span class="tcy">42</span>である。

## 脚注

脚注[^1]は使える。

[^1]: 脚注

## 生のHTMLとLaTeX

使えるらしい。

DivタグとSpanタグ以外は生のHTMLとして使える。

## 絵文字

Cicaフォントに入っているものなら使える……はず。

🍣
