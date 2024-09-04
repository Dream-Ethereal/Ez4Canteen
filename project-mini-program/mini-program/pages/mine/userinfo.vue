<template>
	<view class="container d-flex flex-column">
		<view class="flex-fill form">
			<list-cell :hover="false">
				<view class="form-input w-100 d-flex align-items-center">
					<view class="label">昵称</view>
					<view class="input flex-fill">
						<input type="text" placeholder="请填写昵称" placeholder-class="text-color-assist font-size-base" 
						v-model="member.nickname">
					</view>
				</view>
			</list-cell>
			<list-cell :hover="false">
				<view class="form-input w-100 d-flex align-items-center">
					<view class="label">手机号码</view>
					<view class="input flex-fill">
						<input type="text" v-model="member.mobilePhone" disabled>
					</view>
				</view>
			</list-cell>
			<list-cell :hover="false">
				<view class="form-input w-100 d-flex align-items-center">
					<view class="label">性别</view>
					<view class="input flex-fill">
						<view class="radio-group">
							<view class="radio" :class="{'checked': member.gender == '1'}" style="margin-right: 10rpx;" @tap="member.gender=1">先生</view>
							<view class="radio" :class="{'checked': member.gender == '2'}" @tap="member.gender=2">女士</view>
						</view>
					</view>
				</view>
			</list-cell>
			<list-cell :hover="false" :arrow="!member.birthday">
				<view class="form-input w-100 d-flex align-items-center">
					<view class="label">生日</view>
					<view class="input flex-fill">
						<picker mode="date" :value="date" :start="startDate" :end="endDate" v-if="!member.birthday" @change="handleDateChange">
							点击选择日期
						</picker>
						<!-- <input type="text" v-else :value="member.birthday" > -->
						<picker mode="date" :value="date" :start="startDate" :end="endDate" v-else @change="handleDateChange">
							{{member.birthday}}
						</picker>
					</view>
				</view>
			</list-cell>
			<list-cell :hover="false" last>
				<view class="form-input w-100 d-flex align-items-center">
					<view class="label">入会时间</view>
					<view class="input flex-fill">
						<input type="text" v-model="member.openingCardDate" disabled>
					</view>
				</view>
			</list-cell>
		</view>
		<view class="btn-box d-flex align-items-center just-content-center">
			<button type="primary" class="save-btn" @tap="save">保存</button>
		</view>
	</view>
</template>

<script>
	import listCell from '@/components/list-cell/list-cell'
	import { Member } from '../../api/member.js'
	export default {
		components: {
			listCell
		},
		data() {
			const currentDate = this.getDate({format: true})
			return {
				member: {},
				date: currentDate
			}
		},
		computed: {
		   startDate() {
				return this.getDate('start');
			},
			endDate() {
				return this.getDate('end');
			}
		},
		onLoad() {
			this.member = Member
		},
		mounted() {
		},
		methods: {
			getDate(type) {
				const date = new Date();
				let year = date.getFullYear();
				let month = date.getMonth() + 1;
				let day = date.getDate();
	
				if (type === 'start') {
					year = year - 60;
				} else if (type === 'end') {
					year = year + 2;
				}
				month = month > 9 ? month : '0' + month;;
				day = day > 9 ? day : '0' + day;
				return `${year}-${month}-${day}`;
			},
			handleDateChange(e) {
				this.member.birthday = e.target.value
			},
			save() {
			  // 校验用户输入的信息
			  if (this.member.nickname.trim() === '') {
			    uni.showToast({
			      title: '请填写昵称',
			      icon: 'none'
			    });
			    return;
			  }
			
			  if (this.member.birthday.trim() === '') {
			    uni.showToast({
			      title: '请选择生日日期',
			      icon: 'none'
			    });
			    return;
			  }
			  
			
			  // 调用云函数更新用户信息
			  uniCloud.callFunction({
			    name: 'userManagement',
			    data: {
			      mobilePhone: this.member.mobilePhone,
			      nickname: this.member.nickname,
			      gender: this.member.gender,
			      birthday: this.member.birthday
			    }
			  }).then(res => {
			    if (res.result.success) {
			      // 更新全局变量 Member
				  Object.assign(Member, this.member)
			      this.SET_MEMBER(this.member);
			      
			    }
			  }).catch(error => {
			    
			  });
			  uni.navigateBack();
			}

		}
	}
</script>

<style lang="scss" scoped>
page {
	height: 100%;
}

.container {
	padding: 20rpx 30rpx;
}

.form {
	border-radius: 8rpx;
}

.form-input {
	.label {
		width: 160rpx;
		font-size: $font-size-base;
		color: $text-color-base;
	}
	
	.input {
	}
	
	.radio-group {
		display: flex;
		justify-content: flex-start;
		
		.radio {
			padding: 10rpx 30rpx;
			border-radius: 6rpx;
			border: 2rpx solid $text-color-assist;
			color: $text-color-assist;
			font-size: $font-size-base;
			
			&.checked {
				background-color: $color-primary;
				color: $text-color-white;
				border: 2rpx solid $color-primary;
			}
		}
	}
}

.btn-box {
	height: calc((100vh - 40rpx) / 2);
}

.save-btn {
	width: 90%;
	border-radius: 50rem !important;
	font-size: $font-size-lg;
}
</style>
