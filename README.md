# 井の頭文芸部 本文テンプレート

[![Build books.](https://github.com/huidetang/XiandaiFenshuTemplate/actions/workflows/jobs.yml/badge.svg)](https://github.com/huidetang/XiandaiFenshuTemplate/actions/workflows/jobs.yml)

Sorry, but the book will be written in Japanese, and the project is in Japanese as an official language. If you can read and write Japanese, you are welcome to contribute.

井の頭文芸部で作った、[Re:VIEW](https://github.com/kmuto/review)用日本語縦書きテンプレートです。

ビルドに[Vivliostyle](https://vivliostyle.org/ja/)を使用します。

旧LaTeX版の設定も併記しています。

図は[Mermaid](https://mermaid.js.org/)が使えます。

もちろん、PNG形式などの画像ファイルにも対応しています。これらの画像ファイルは `images` フォルダーに配置してください。

なお、印刷用PDFではカラー画像はモノクロ画像に変換されます。

本文はRe:VIEW記法の他に、MarkdownとMicrosoft Wordに対応しています。しかし、Microsoft Word文書では書式が全て無視される上、縦中横が効かないなどいろいろな制約がありますのでご注意ください。これらの本文ファイルは `chapter` フォルダーに配置し、 `catalog.yml` ファイルに記載してください。なお、記載する際にMarkdownとMicrosoft Word文書の拡張子は `.re` に変更する必要があります。

後は、[Re:VIEWのドキュメント](https://github.com/kmuto/review/blob/master/doc/format.ja.md)を参照の上で書籍を書いてみてください。

なお、GitHub Actionsによるビルドを自動で実行する設定がついていますので、GitとGitHubの使い方を覚えれば執筆できる環境が揃うと思います。

## おすすめの環境

おすすめの環境は以下の通りです。

- エディタ : Visual Studio Code
- Linuxコンテナ環境 : Docker Desktop
- ソースコード管理 : GitHub

詳しい説明は別途追記します。

## ライセンスについて （About LICENSE）

このテンプレートはMITライセンスです。