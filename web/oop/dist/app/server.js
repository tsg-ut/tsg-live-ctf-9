const express = require('express');
const qs = require('querystring');
const bodyParser = require('body-parser');
const strokes = require('./strokes.json')

const app = express();

app.set('view engine', 'ejs')

app.use(express.static('public'));
app.use(bodyParser.urlencoded({extended: false}))

app.post('/report', async (req, res) => {
	try {
		const result = await fetch('http://reporter:8080/report', {
			method: 'POST',
			headers: {
				'content-type': 'application/x-www-form-urlencoded',
			},
			body: qs.encode({
				name: req.body.name ?? '',
			}),
		});
		res.send(await result.text());
	} catch (e) {
		console.error(e);
	}
});

app.get('/getStrokes', (req, res) => {
	const name = req.query.name ?? '';
	const data = {};
	for (const char of name) {
		data[char] = strokes[char] ?? 0;
	}
	res.json(data);
});

app.get('/', (req, res) => {
	res.render('index', {name: req.query.name});
});

app.listen(56520);