import Vue from 'vue'
import Vuex from 'vuex'
import api from '@/api'
var mqtt = require('../util/mqtt.min.js'); // 引入 mqtt 库
const crypto = require('../util/hex_hmac_sha1.js'); //根据自己存放的路径修改
Vue.use(Vuex)

const store = new Vuex.Store({
	state: {
		store: {},
		cart: [],
		orderType: 'takein',
		member: {},
		order: {},
		client: null,
		mqtt: mqtt,
		isConnect: false
	},
	getters: {
		isLogin: state => Object.keys(state.member).length > 0	//是否登录
	},
	mutations: {
		SET_ORDER_TYPE(state, type) {
			state.orderType = type
		},
		SET_MEMBER(state, member) {
			state.member = member
		},
		SET_STORE(state, store) {
			state.store = store
		},
		SET_CART(state, cart) {
			state.cart = cart
		},
		REMOVE_CART(state) {
			state.cart = []
		},
		SET_ORDER(state, order) {
			state.order = order
		},
		SET_ORDERS(state, orders) {
		  // 直接修改 state 的 Member.orders
		  state.Member.orders = orders;
		},
		UPDATE_MEMBER(state, memberData) {
		  // 直接修改 state 的 Member
		  Object.assign(state.Member, memberData);
		},
		setClient(state, client) {
			state.client = client;
		},
	},
	actions: {
	  async getStore({ commit }) {
	    const store = await api('store');
	    commit('SET_STORE', store);
	  },
	  updateOrders({ commit }, orders) {
	    commit('SET_ORDERS', orders);
	  },
	  updateMember({ commit }, memberData) {
	    commit('UPDATE_MEMBER', memberData);
	  },
	  connectMqtt({ commit, state }) {
		if(state.isConnect)
		{
			return;
		}
	    const deviceConfig = {
	          productKey: "k1n5mcDd3Fr",
	          deviceName: "mini",
	          deviceSecret: "fc91ea19f38ca586285eadcb72a5bd71",
	          regionId: "cn-shanghai"
	        };

			const params = {
			      productKey: deviceConfig.productKey,
			      deviceName: deviceConfig.deviceName,
			      timestamp: Date.now(),
			      clientId: Math.random().toString(36).substr(2),
			    }
			//CONNECT参数
			const options = {
			  keepalive: 60, //60s
			  clean: true, //cleanSession不保持持久会话
			  protocolVersion: 4 //MQTT v3.1.1
			}
			//1.生成clientId，username，password
			
			
			let keys = Object.keys(params).sort();
			// 按字典序排序
			keys = keys.sort();
			const list = [];
			keys.map((key) => {
			  list.push(`${key}${params[key]}`);
			});
			const contentStr = list.join('');
			options.password = crypto.hex_hmac_sha1(deviceConfig.deviceSecret, contentStr);
			
			options.clientId = `${params.clientId}|securemode=2,signmethod=hmacsha1,timestamp=${params.timestamp}|`;
			options.username = `${params.deviceName}&${params.productKey}`;
			
	        console.log(options)
	        //替换productKey为你自己的产品的（注意这里是wxs，不是wss，否则你可能会碰到ws不是构造函数的错误）
	        state.client = mqtt.connect('wxs://k1n5mcDd3Fr.iot-as-mqtt.cn-shanghai.aliyuncs.com',options)
	        state.client.on('connect', function () {
			  state.isConnect = true;
	          console.log('连接服务器成功')
	          //注意：订阅主题，替换productKey和deviceName(这里的主题可能会不一样，具体请查看控制台-产品详情-Topic 类列表下的可订阅主题)，并且确保改主题的权限设置为可订阅
	          state.client.subscribe('/k1n5mcDd3Fr/mini/user/get', function (err) {
	            if (!err) {
	               console.log('订阅成功！');
	            }
	          })
	        })
	    	//接收消息监听
	        state.client.on('message', function (topic, message) {
	          // message is Buffer
	          let msg = message.toString();
	          console.log('收到消息：'+msg);
	         //关闭连接 client.end()
			})
	  },
	  
	}

})

export default store