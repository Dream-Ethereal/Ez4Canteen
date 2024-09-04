import Vue from 'vue'
import App from './App'
import api from './api'
import util from './common/util'
import store from './store'
// import member from '@/api/member.js'

Vue.config.productionTip = false

App.mpType = 'app'

Vue.prototype.$store = store
Vue.prototype.$api = api
Vue.prototype.$util = util

// Vue.prototype.$Member = member

const app = new Vue({
	store,
    ...App
})
app.$mount()
