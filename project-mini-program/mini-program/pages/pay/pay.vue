<template>
	<scroll-view scroll-y="true" >
		
	
	<view class="container position-relative">
		<view style="margin-bottom: 130rpx;">
			<view class="section-1">
				<template v-if="orderType == 'takein'">
					<list-cell class="location">
						<view class="flex-fill d-flex justify-content-between align-items-center">
							<view class="store-name flex-fill">
								恩溪烧烤店
							</view>
							<image src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/navigator-1.png" class="arrow"></image>
						</view>
					</list-cell>
				</template>
				<template v-else>
					<list-cell @click="chooseAddress">
						<view class="w-100 d-flex flex-column">
							<view class="d-flex align-items-center justify-content-between mb-10">
								<view class="font-size-extra-lg text-color-base">{{ address.street }}</view>
								<image src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/navigator-1.png" class="arrow"></image>
							</view>
							<view class="d-flex text-color-assist font-size-sm align-items-center">
								<view class="mr-10">{{ address.accept_name }}</view>
								<view class="mr-10">{{ !address.sex ? '先生' : '女士' }}</view>
								<view>{{ address.mobile }}</view>
							</view>
						</view>
					</list-cell>
				</template>
				<template v-if="orderType == 'takein'">
					<list-cell arrow class="meal-time">
						<view class="flex-fill d-flex justify-content-between align-items-center">
							<view class="title">取餐时间</view>
							<view class="time">立即用餐</view>
						</view>
					</list-cell>
					<list-cell class="contact" last :hover="false">
						<view class="flex-fill d-flex justify-content-between align-items-center">
							<view class="title flex-fill">联系电话</view>
							<view class="time">
								<input class="text-right" placeholder="请输入手机号码" v-model="mobilePhone"/>
							</view>
							<view class="contact-tip font-size-sm">自动填写</view>
						</view>
					</list-cell>
					<list-cell class="dining-options" last :hover="false">
						<view class="flex-fill d-flex justify-content-between align-items-center">
							<view class="title flex-fill">选择方式</view>
							<view class="options d-flex">
								<view class="option" @click="selectOption('堂食')" :class="{ selected: diningOption === '堂食' }">
									堂食
								</view>
								<view class="option" @click="selectOption('打包')" :class="{ selected: diningOption === '打包' }">
									打包
								</view>
							</view>
						</view>
					</list-cell>
				</template>
				
				<!-- <template v-else>
					<list-cell>
						<view class="w-100 d-flex flex-column">
							<view class="d-flex align-items-center font-size-base text-color-base">
								<view class="flex-fill">预计送达时间</view>
								<view class="mr-10">15:18</view>
								<image src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/navigator-1.png" class="arrow"></image>
							</view>
							<view class="font-size-base text-color-primary">
								特殊时期减少接触，请修改下方订单备注
							</view>
						</view>
					</list-cell>
				</template> -->
			</view>
			<!-- 购物车列表 begin -->
			<view class="section-2">
				<view class="cart d-flex flex-column">
					<list-cell last v-for="(item, index) in cart" :key="index">
						<view class="w-100 d-flex flex-column">
							<view class="d-flex align-items-center mb-10">
								<view class="name-and-props overflow-hidden">
									<view class="text-color-base font-size-lg">
										{{ item.name }}
									</view>
								</view>
								<view class="d-flex flex-fill justify-content-between align-items-center text-color-base font-size-lg">
									<view>x{{ item.number }}</view>
									<view>￥{{ item.price }}</view>
								</view>
							</view>
							<!-- <view class="text-truncate font-size-base text-color-assist">
								{{ item.props_text }}
							</view> -->
						</view>
					</list-cell>
					<!-- <template v-if="orderType == 'takeout'">
						<list-cell last v-if="store.packing_fee > 0">
							<view class="w-100 d-flex font-size-base align-items-center justify-content-between">
								<view>包装费</view>
								<view>￥{{ parseFloat(store.packing_fee) }}</view>
							</view>
						</list-cell>
						<list-cell last v-if="store.delivery_cost > 0">
							<view class="w-100 d-flex font-size-base align-items-center justify-content-between">
								<view>配送费</view>
								<view>￥{{ parseFloat(store.delivery_cost) }}</view>
							</view>
						</list-cell>
					</template> -->
				</view>
				<!-- <list-cell arrow @click="goToPackages">
					<view class="flex-fill d-flex justify-content-between align-items-center">
						<view class="text-color-base">奈雪券</view>
						<view class="text-color-primary">超值购买优惠券大礼包</view>
					</view>
				</list-cell>
				<list-cell arrow>
					<view class="flex-fill d-flex justify-content-between align-items-center">
						<view class="text-color-base">礼品卡</view>
						<view class="text-color-primary">请选择</view>
					</view>
				</list-cell> -->
				<list-cell last>
					<view class="flex-fill d-flex justify-content-end align-items-center">
						<view>总计￥{{ total }},实付</view>
						<view class="font-size-extra-lg font-weight-bold">￥{{ amount }}</view>
					</view>
				</list-cell>
			</view>
			<!-- 购物车列表 end -->
			<view class="d-flex align-items-center justify-content-start font-size-sm text-color-warning" 
				style="padding: 20rpx 0;">
				<view class="iconfont iconhelp line-height-100"></view>
				<view>优惠券不与满赠、满减活动共享</view>
			</view>
			<!-- 支付方式 begin -->
			<view class="payment">
				<list-cell last :hover="false">
					<text>支付方式</text>
				</list-cell>
				<!-- <list-cell>
					<view class="d-flex align-items-center justify-content-between w-100 disabled">
						<view class="iconfont iconbalance line-height-100 payment-icon"></view>
						<view class="flex-fill">余额支付（余额￥0）</view>
						<view class="font-size-sm">余额不足</view>
						<view class="iconfont iconradio-button-off line-height-100 checkbox"></view>
					</view>
				</list-cell> -->
				<list-cell last>
					<view class="d-flex align-items-center justify-content-between w-100">
						<view class="iconfont iconwxpay line-height-100 payment-icon" style="color: #7EB73A;"></view>
						<view class="flex-fill">微信支付</view>
						<view class="iconfont iconradio-button-on line-height-100 checkbox checked"></view>
					</view>
				</list-cell>
			</view>
			<!-- 支付方式 end -->
			<!-- 备注 begin -->
			<list-cell arrow last @click="goToRemark">
				<view class="d-flex flex-fill align-items-center justify-content-between overflow-hidden">
					<view class="flex-shrink-0 mr-20">备注</view>
					<view class="text-color-primary flex-fill text-truncate text-right">{{ form.remark || '点击填写备注' }}</view>
				</view>
			</list-cell>
			<!-- 备注 end -->
		</view>
		<!-- 付款栏 begin -->
		<view class="w-100 pay-box position-fixed fixed-bottom d-flex align-items-center justify-content-between bg-white">
			<view class="font-size-sm" style="margin-left: 20rpx;">合计：</view>
			<view class="font-size-lg flex-fill">￥{{ amount }}</view>
			<view class="bg-primary h-100 d-flex align-items-center just-content-center text-color-white font-size-base"
				style="padding: 0 60rpx;" @tap="submit">
				付款
			</view>
		</view>
		<!-- 付款栏 end -->
		<modal :show="ensureAddressModalVisible" custom :mask-closable="false" :radius="0" width="90%">
			<view class="modal-content">
				<view class="d-flex justify-content-end">
					<image src="/static/images/pay/close.png" style="width: 40rpx; height: 40rpx;" @tap="ensureAddressModalVisible=false"></image>
				</view>
				<view class="d-flex just-content-center align-items-center" style="margin-bottom: 40px;">
					<view class="font-size-extra-lg text-color-base">请再次确认下单地址</view>
				</view>
				<view class="d-flex font-size-base text-color-base font-weight-bold align-items-center justify-content-between mb-20">
					<view>{{ address.accept_name }} {{ address.sex ? '女士' : '先生' }}</view>
					<view>{{ address.mobile }}</view>
				</view>
				<view class="d-flex font-size-sm text-color-assist align-items-center justify-content-between mb-40">
					<view>{{ address.street + address.door_number }}</view>
					<button type="primary" size="mini" plain class="change-address-btn">修改地址</button>
				</view>
				<button type="primary" class="pay_btn" @tap="pay">确认并付款</button>
			</view>
		</modal>
	</view>
	</scroll-view>
</template>

<script>
	import {mapState, mapMutations} from 'vuex'
	import listCell from '@/components/list-cell/list-cell'
	import modal from '@/components/modal/modal'
	import { Member } from '../../api/member.js'
	// var mqtt = require('../../util/mqtt.min.js')
	
	function getCurrentTimestamp() {
	    const now = new Date();
	    const offset = 8 * 60 * 60 * 1000;  // 北京时间偏移（8小时）
	    const localTime = new Date(now.getTime() + offset);
	    return localTime.toISOString().slice(0, 19).replace('T', ' ');
	}


	export default {
		components: {
			listCell,
			modal
		},
		data() {
			return {
				diningOption: "堂食",
				cart: [],
				form: {
					remark: ''
				},
				ensureAddressModalVisible: false,
				mobilePhone: ""
			}
		},
		computed: {
			...mapState(['orderType', 'address', 'store', 'client']),
			total() {
				return this.cart.reduce((acc, cur) => acc + cur.number * cur.price, 0)
			},
			amount() {
				return this.cart.reduce((acc, cur) => acc + cur.number * cur.price, 0)
			}
		},
		onLoad(option) {
			// var that = this;
			// that.connetMqtt();
			this.mobilePhone = Member.mobilePhone;
			const {remark} = option
			this.cart = uni.getStorageSync('cart')
			remark && this.$set(this.form, 'remark', remark)
		},
		methods: {
		    ...mapMutations(['SET_ORDER']),
		    goToRemark() {
		        uni.navigateTo({
		            url: '/pages/remark/remark?remark=' + this.form.remark
		        });
		    },
		    chooseAddress() {
		        uni.navigateTo({
		            url: '/pages/address/address?is_choose=true&scene=pay'
		        });
		    },
		    goToPackages() {
		        uni.navigateTo({
		            url: '/pages/packages/index'
		        });
		    },
		    submit() {
		        if (this.orderType === 'takeout') {
		            this.ensureAddressModalVisible = true;
		        } else {
		            this.addOrderToMember(); // Add order before payment
		            this.updateUserInfoInDatabase(); // Update database
					
					
					
		            this.pay(); // Process payment
		        }
		    },
		    addOrderToMember() {
		        const currentTimestamp = getCurrentTimestamp();
		        const orderNo = (Math.floor(Date.now() / 1000) + 40000000000).toString();
		        const totalAmount = this.cart.reduce((sum, item) => sum + (parseFloat(item.price) * item.number), 0).toFixed(2);
		    
		        const newOrder = {
		            pay_mode: "微信支付",
		            goods_num: this.cart.reduce((sum, item) => sum + item.number, 0),
		            status_text: "已完成",
		            remark: this.form.remark,
		            mobile: Member.mobilePhone,
		            user_name: Member.nickname,
		            store: {
		                name: "恩溪烧烤店"
		            },
		            completed_time: currentTimestamp,
		            amount: totalAmount,
		            productioned_time: currentTimestamp,
		            postscript: this.diningOption,
		            sort_num: Member.mobilePhone.slice(-4),
		            order_no: orderNo,
		            review: {},
		            goods: this.cart.map(item => ({
		                number: item.number,
		                price: item.price,
		                image: item.image,
		                amount: (item.price * item.number).toFixed(2),
		                name: item.name
		            }))
		        };
		    
		        // Update Member.orders
		        Member.orders.unshift(newOrder);
		    
		        // Update Member.pointNum
		        Member.pointNum += parseFloat(totalAmount);
		    
		        this.sendBillToMQTT(newOrder);
		    
		        // Update sales in shop_list
		        const db = uniCloud.database();
		    
		        this.cart.forEach(async (cartItem) => {
		            try {
		                const res = await db.collection('shop_list').where({
		                    'goods_list.id': cartItem.id
		                }).get();
		    
		                if (res.result.data.length > 0) {
		                    const shopItem = res.result.data[0];
		                    const goodsIndex = shopItem.goods_list.findIndex(g => g.id === cartItem.id);
		    
		                    if (goodsIndex !== -1) {
		                        // Update the sales attribute
		                        const updatedGoods = shopItem.goods_list;
		                        updatedGoods[goodsIndex].sales += cartItem.number;
		    
		                        // Update the shop_list with the modified goods_list
		                        await db.collection('shop_list').doc(shopItem._id).update({
		                            goods_list: updatedGoods
		                        });
		                    }
		                }
		            } catch (error) {
		                console.error(`Error updating sales for item ${cartItem.id}:`, error);
		            }
		        });
		    },
		    async updateUserInfoInDatabase() {
		        try {
		            await uniCloud.callFunction({
		                name: 'updateUserInfo', // Cloud function name
		                data: {
		                    mobilePhone: Member.mobilePhone,
		                    updateData: {
		                        orders: Member.orders,
		                        pointNum: Member.pointNum
		                    }
		                }
		            });
		        } catch (error) {
		            console.error('更新用户信息失败', error);
		        }
		    },
			selectOption(option) {
				this.diningOption = option;
			},
		    pay() {
		        uni.showLoading({ title: '加载中' });
		
		        // Test order
		
		        uni.removeStorageSync('cart');
		
		        // Redirect to another page
		        uni.reLaunch({
		            url: '/pages/orders/orders'
		        });
		
		        uni.hideLoading();
		    },
			sendBillToMQTT(order) {
			  // 获取所需的属性
			  const sortNum = order.sort_num || '';
			  const postscript = order.postscript || '';
			  const completedTime = order.completed_time || '';
			  const remark = order.remark || '';
			  const goodsDetails = order.goods.map(good => {
			    return {
			      name: good.name,
			      price: good.price,
			      number: good.number,
			      amount: good.amount
			    };
			  });
			  const amount = order.amount || '';
			  const userName = order.user_name.charAt(0) + '****' || '';
			  const mobile = order.mobile.replace(/(\d{3})\d{4}(\d{4})/, '$1****$2') || '';
			  const orderNo = order.order_no || '';
			  const TargetDevice = "Ez4Canteen-esp8266";
			
			  // 构造 JSON 对象
			  const bill = {
			    sortNum: sortNum,
			    postscript: postscript,
			    completedTime: completedTime,
			    remark: remark,
			    goodsDetails: goodsDetails,
			    amount: amount,
			    userName: userName,
			    mobile: mobile,
			    orderNo: orderNo,
				TargetDevice: TargetDevice
			  };
			
			  // 将 JSON 对象转换为字符串并通过 MQTT 发布
			  this.client.publish('/k1n5mcDd3Fr/mini/user/update', JSON.stringify(bill));
			}
		}

	}

</script>

<style lang="scss" scoped>
	.container {
		padding: 30rpx;
	}
	
	.arrow {
		width: 50rpx; 
		height: 50rpx;
		position: relative;
		margin-right: -10rpx;
	}
	
	.location {
		.store-name {
			font-size: $font-size-lg;
		}
		
		.iconfont {
			font-size: 50rpx;
			line-height: 100%;
			color: $color-primary;
		}
	}
	
	.section-1 {
		margin-bottom: 30rpx;
		.contact {
			.contact-tip {
				margin-left: 10rpx;
				border: 2rpx solid $color-primary;
				padding: 6rpx 10rpx;
				color: $color-primary;
			}
		}
	}
	
	.section-2 {
		.name-and-props {
			width: 65%;
		}
	}
	
	.dining-options {
		margin-top: 10rpx;
	}
	.options {
		display: flex;
	}
	.option {
		border: 1px solid #ccc;
		padding: 5px 10px;
		margin-right: 10px;
		cursor: pointer;
	}
	.option.selected {
		background-color: #d8e0a7;
		color: white;
		border-color: #d8e0a7;
	}
	
	.payment {
		margin-bottom: 30rpx;
		
		.disabled {
			color: $text-color-grey;
		}
		
		.payment-icon {
			font-size: 44rpx; 
			margin-right: 10rpx;
		}
		
		.checkbox {
			font-size: 36rpx;
			margin-left: 10rpx;
		}
		
		.checked {
			color: $color-primary;
		}
	}
	
	.pay-box {
		box-shadow: 0 0 20rpx rgba(0, 0, 0, .1);
		height: 100rpx;
	}
	
	.modal-content {
		.change-address-btn {
			line-height: 2;
			padding: 0 1em;
		}
		.pay_btn {
			width: 100%;
			border-radius: 50rem !important;
			line-height: 3;
		}
	}
</style>
