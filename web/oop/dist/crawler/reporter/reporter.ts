import Redis from 'ioredis';
import express from 'express';
import bodyParser from 'body-parser';

const app = express();
app.use(bodyParser());

const connection = new Redis(6379, 'redis');
connection.set('queued_count', 0);
connection.set('proceeded_count', 0);

app.post('/report', async (req, res) => {
	try {
		if (typeof req.body.name === 'string' && req.body.name !== ''){
			await connection.rpush('query', req.body.name);
			await connection.incr('queued_count');
			console.log(`[*] Queried: ${req.body.name}`);
		}
		res.send('Okay! I got it :-)');
	} catch (e) {
		console.error(e);
		res.send('Umm, there is something wrong ...');
	}
});

app.listen(8080, () => {
	console.log(`Publisher is listening`);
});
