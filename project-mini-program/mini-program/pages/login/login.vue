<template>
  <view class="container">
    <view class="intro">
      <image src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/logo.png"></image>
      <view class="tips">
        美食就在眼前
        <br>
        快来尽情挑选吧~
      </view>
    </view>

    <view class="bottom">
      <!-- 登录表单 -->
      <view v-if="!isRegistering">
        <input class="input-field" v-model="phone" type="text" placeholder="请输入手机号"  />
        <input class="input-field" v-model="password" type="password" placeholder="请输入密码" />
        <button type="primary" size="default" class="login-btn" @tap="login">
          登录
        </button>
        <button type="primary" size="default" class="register-btn" @tap="toggleRegister">
          注册
        </button>
      </view>

      <!-- 注册表单 -->
      <view v-if="isRegistering">
        <input class="input-field" v-model="phone" type="text" placeholder="请输入手机号" />
        <input class="input-field" v-model="password" type="password" placeholder="请输入密码" />
        <input class="input-field" v-model="confirmPassword" type="password" placeholder="确认密码" />
        <button type="primary" size="default" class="register-btn" @tap="register">
          完成注册
        </button>
        <button type="primary" size="default" class="register-btn" @tap="toggleRegister">
          取消
        </button>
      </view>

      <!-- 微信登录按钮 -->
      <!-- <button v-if="!isRegistering && !isLoggedIn" type="primary" size="default" class="login-btn" open-type="getUserInfo" lang="zh_CN" @getuserinfo="getUserInfo">
        <image src="/static/images/mine/wechat.png"></image>
        微信一键登录
      </button> -->

      <view class="d-flex flex-column justify-content-evenly align-items-center text-center" style="height: 30vh;">
        <view class="w-100 font-size-base text-color-assist">新用户登录即加入会员，享会员权益</view>
        <view class="w-100 row d-flex just-content-around align-items-center font-size-sm text-color-assist">
          <view class="grid">
            <image src="/static/images/mine/rhyl.png"></image>
            <view>入会有礼</view>
          </view>
          <view class="grid">
            <image src="/static/images/mine/jfdh.png"></image>
            <view>积分兑换</view>
          </view>
        </view>
        <view class="font-size-base text-color-primary">会员权益说明</view>
      </view>
    </view>
  </view>
</template>

<script>
  import { mapMutations , mapGetters} from 'vuex'
  import { Member } from '../../api/member.js';
  export default {
    data() {
      return {
        phone: '13587670732',
        password: '1',
        confirmPassword: '',
        isRegistering: false,
        isLoggedIn: false
      }
    },
    methods: {
	  ...mapGetters(['isLogin']),
      ...mapMutations(['SET_MEMBER']),

      toggleRegister() {
        this.isRegistering = !this.isRegistering;
      },

      async login() {
        // 登录逻辑
        if (!this.phone || !this.password) {
          uni.showToast({
            title: '手机号和密码不能为空',
            icon: 'none'
          });
          return;
        }
       
        try {
          // 调用云函数验证用户
          const res = await uniCloud.callFunction({
            name: 'validateUser',
            data: {
              phone: this.phone,
              password: this.password
            }
          });
		  
          if (res.result.success) {
			// 登录成功，更新全局变量 Member
			Object.assign(Member, res.result.user);
			this.SET_MEMBER(res.result.user);

            uni.showToast({
              title: '登录成功',
              icon: 'success'
            });
            uni.navigateBack();
          } else {
            // 登录失败，提示用户
            uni.showToast({
              title: '手机号或密码不正确，请重新输入',
              icon: 'none'
            });
          }
        } catch (error) {
          console.error('登录失败', error);
          uni.showToast({
            title: '登录失败',
            icon: 'none'
          });
        }
      },


	async register() {
	  // 注册逻辑
	  if (!this.phone || !this.password || !this.confirmPassword) {
		uni.showToast({
		  title: '手机号、密码和确认密码不能为空',
		  icon: 'none'
		});
		return;
	  }

	  if (this.password !== this.confirmPassword) {
		uni.showToast({
		  title: '两次密码输入不一致',
		  icon: 'none'
		});
		return;
	  }

	  // 验证手机号格式
	  const phoneRegex = /^[1][3-9][0-9]{9}$/;
	  if (!phoneRegex.test(this.phone)) {
		uni.showToast({
		  title: '手机号格式不正确',
		  icon: 'none'
		});
		return;
	  }

	  try {
		// 检查手机号是否已存在
		const checkRes = await uniCloud.callFunction({
		  name: 'checkPhoneExist',
		  data: {
			phone: this.phone
		  }
		});

		if (checkRes.result.exists) {
		  uni.showToast({
			title: '手机号已被注册',
			icon: 'none'
		  });
		  return;
		}

		// 当前时间
		const now = new Date();
		const secondsSinceEpoch = Math.floor(now.getTime() / 1000);

		// 格式化当前时间为 YY-MM-DD hh:mm:ss
		const formattedDate = now.toISOString().replace('T', ' ').slice(0, 19);

		// 生成 customerId
		const customerId = `USR${secondsSinceEpoch}`;

		// 更新用户数据
		const newUser = {
		  _id:customerId,
		  mobilePhone: this.phone,
		  avatar: "/static/images/mine/default.png",
		  cardName: "V0",
		  memberLevel: 1,
		  birthday: "",
		  pointNum: 0,
		  balance: 0,
		  needValue: 9999999,
		  orders: [],
		  nickname: this.phone,
		  openingCardDate: formattedDate,
		  password: this.password
		};

		// 注册用户
		const registerRes = await uniCloud.callFunction({
		  name: 'registerUser',
		  data: {
			newUser
		  }
		});

		if (registerRes.result.success) {
		  // 更新全局变量 Member
		  Object.assign(Member, newUser);

		  this.SET_MEMBER(newUser);

		  this.isRegistering = false;

		  uni.showToast({
			title: '注册成功',
			icon: 'success'
		  });
		} else {
		  uni.showToast({
			title: '注册失败',
			icon: 'none'
		  });
		}

	  } catch (error) {
		console.error('注册失败', error);
		uni.showToast({
		  title: '注册失败',
		  icon: 'none'
		});
	  }
	}



      
    }
  }
</script>

<style lang="scss" scoped>
  .intro {
    width: 100%;
    height: 30vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: space-evenly;
    font-size: $font-size-base;
    color: $text-color-assist;

    image {
      width: 165rpx;
      height: 165rpx;
    }

    .tips {
      line-height: 72rpx;
      text-align: center;
    }
  }

  .bottom {
    height: 40vh;
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    padding: 0 40rpx;

    .login-btn, .register-btn {
      width: 100%;
      border-radius: 50rem !important;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 10rpx 0;
    }

    .login-btn {
      background-color: #d8e0a7;
      color: #333333;
    }

    .register-btn {
      background-color: #d8e0a7;
      color: #333333;
      margin-top: 10rpx;
    }

    .input-field {
      width: 100%;
      height: 44px;
      border: 1px solid #ccc;
      border-radius: 22px;
      padding: 0 15px;
      box-sizing: border-box;
      margin-bottom: 10rpx;
      text-align: center;
      font-size: 16px;
    }

    .row {
      .grid {
        width: 20%;
        image {
          width: 60rpx;
          height: 60rpx;
          margin-bottom: 10rpx;
        }
      }
    }
  }
</style>
