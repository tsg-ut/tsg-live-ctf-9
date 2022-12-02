import Vue from 'https://unpkg.com/vue@2/dist/vue.esm.browser.js'

const luckinesses = ["凶","大吉","凶","大吉","凶","大吉","大吉","吉","吉","凶","凶","大吉","凶","大吉","凶","大吉","大吉","吉","吉","凶","凶","大吉","凶","大吉","大吉","大吉","凶","吉凶混合","凶","大吉","吉凶混合","大吉","大吉","大吉","凶","吉","吉凶混合","大吉","吉","大吉","吉凶混合","大吉","吉凶混合","凶","凶","大吉","凶","大吉","大吉","凶","凶","吉凶混合","大吉","吉凶混合","凶","吉凶混合","凶","吉","吉","凶","凶","吉","凶","大吉","凶","大吉","凶","大吉","大吉","凶","凶","吉凶混合","吉凶混合","吉凶混合","凶","吉凶混合","凶","吉凶混合","吉凶混合","凶","凶","大吉"];

new Vue({
	el: '#app',
	data () {
		const params = new URLSearchParams(window.location.search);
		return {
			name: params.get('name') ?? '山田 太郎',
			strokes: {},
		}
	},
	mounted() {
		this.updateStrokes(this.name);
	},
	computed: {
		chunks() {
			return this.name.split(' ').map((chunk) => (
				Array.from(chunk)
			));
		},
		totalStrokes() {
			return Array.from(this.name)
				.map((char) => this.strokes[char] ?? 0)
				.reduce((a, b) => a + b, 0);
		},
		luckiness() {
			return luckinesses[this.totalStrokes % luckinesses.length];
		},
	},
	watch: {
		name(newName) {
			this.updateStrokes(newName);
		},
	},
	methods: {
		async updateStrokes(name) {
			const ret = await fetch(`/getStrokes?name=${name}`);
			this.strokes = await ret.json();
		},
		share() {
			const url = new URL(location.href);
			url.searchParams.set('name', this.name);
			alert(`シェアURL: ${url.toString()}`);
		},
	}
});
