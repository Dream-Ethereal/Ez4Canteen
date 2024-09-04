<template>
	<view class="container">
		<view class="content">
			<list-cell last class="mb-20" :hover="false">
				<view class="w-100 d-flex justify-content-between align-items-center">
					<view class="font-size-lg text-color-base flex-fill">{{ storename }}</view>
					<view class="font-size-base text-color-assist mr-10">{{ date }}</view>
					<view class="font-size-base text-color-assist">{{ postscript }}</view>
				</view>
			</list-cell>
			<view class="review-form">
				<view class="review-rate-form mb-20">
					<rate-form-item v-model="form.score_service" label="服务" tips="能感受到良好的服务态度吗？"></rate-form-item>
					<rate-form-item v-model="form.score_order" label="点单" tips="点单有恰当的介绍，快速准确地下单吗？"></rate-form-item>
					<rate-form-item v-model="form.score_speed" label="速度" tips="出品的速度您认为可接受吗？"></rate-form-item>
					<rate-form-item v-model="form.score_product" label="产品" tips="您享用的菜品，如您所期待吗？"></rate-form-item>
					<rate-form-item v-model="form.score_enviroment" label="环境" tips="店内环境和清洁卫生，您满意吗？"></rate-form-item>
				</view>
				<view class="review-textarea-form">
					<textarea v-model="form.opinion" placeholder="如果您有什么意见和建议,请告诉我们,我们会认真聆听" 
					placeholder-class="font-size-sm text-color-assist"/>
					<view class="text-right font-size-sm text-color-assist">{{ form.opinion.length }}/500</view>
				</view>
			</view>
		</view>
		<view class="btn-box">
			<button type="primary" @tap="submit">提交评论</button>
		</view>
	</view>
</template>

<script>
	import listCell from '@/components/list-cell/list-cell'
	import rateFormItem from './rate-form-item'
	import { Member } from '../../api/member'

	export default {
		components: {
			listCell,
			rateFormItem
		},
		data() {
			return {
				form: {
					score_service: 0,
					score_order: 0,
					score_speed: 0,
					score_product: 0,
					score_enviroment: 0,
					opinion: ''
				},
				storename: '',
				postscript: "",
				date: '',
				order_no: ""
			}
		},
		onLoad({storename, postscript, date, order_no}) {
			this.storename = storename
			this.postscript = postscript
			this.date = date
			this.order_no = order_no
			console.log(this.order_no)
		},
		methods: {
			async submit() {
				if(!this.form.score_service || !this.form.score_order || !this.form.score_speed || !this.form.score_product || !this.form.score_enviroment){
					uni.showToast({
						title: '请先选择评论内容',
						icon: 'none'
					})
					return
				}
				
				// 查找对应的订单
				const orderIndex = Member.orders.findIndex(order => order.order_no === this.order_no);
				if (orderIndex !== -1) {
					// 更新订单的 review 属性
					this.$set(Member.orders[orderIndex], 'review', this.form);
					console.log(Member)
					// 更新本地 Member 对象
					await this.updateMemberInfoInDatabase();

					uni.showToast({
						title: '提交成功'
					})

					uni.navigateBack()
				} else {
					uni.showToast({
						title: '订单未找到',
						icon: 'none'
					})
				}
			},
			async updateMemberInfoInDatabase() {
				try {
					await uniCloud.callFunction({
						name: 'updateUserInfo', // 云函数名称
						data: {
							mobilePhone: Member.mobilePhone,
							updateData: {
								orders: Member.orders
							}
						}
					});
				} catch (error) {
					console.error('更新用户信息失败', error);
				}
			}
		}
	}

</script>

<style lang="scss" scoped>
	.content {
		padding-bottom: 120rpx;
	}
	
	.btn-box {
		position: fixed;
		bottom: 0;
		left: 0;
		right: 0;
		height: 120rpx;
		background-color: #FFFFFF;
		padding: 20rpx 0;
		display: flex;
		justify-content: center;
		
		button {
			width: 90%;
			height: 100%;
			display: flex;
			align-items: center;
			justify-content: center;
			border-radius: 50rem !important;
		}
	}
	
	.review-form {
		background-color: #FFFFFF;
		padding: 20rpx 0;
	}
	
	.review-textarea-form {
		padding: 0 30rpx;
		
		textarea {
			width: 100%;
			background-color: $bg-color;
			padding: 30rpx;
			font-size: $font-size-sm;
			color: $font-size-base;
		}
	}
</style>
