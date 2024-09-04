<template>
  <view class="fix-top-window">
    <!-- 欢迎界面 -->
    <view class="welcome-container">
      <image class="logo" src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/logo.png" /> <!-- 替换为实际的 logo 图片路径 -->
      <view class="welcome-text">
        欢迎来到Ez4Canteen后台管理系统， {{ userInfo.username }} ！<!-- 使用模板语法显示用户名 -->
      </view>
    </view>
	<!-- #ifndef H5 -->
	<fix-window />
	<!-- #endif -->
  </view>
</template>


<script>
export default {
  data() {
    return {
      userName: '用户名' // 在实际应用中应动态获取用户名
    };
  },
  computed: {
  	userInfo () {
  		return this.$uniIdPagesStore.store.userInfo
		}
   },
};
</script>

<style>
/* 全局样式和其他组件样式 */

.fix-top-window {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 90vh; /* 使容器占满整个视口高度 */
  text-align: center; /* 使内容居中对齐 */
}

.welcome-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

.logo {
  width: 200px; /* 调整为适合的宽度 */
  height: 200px; /* 保持图片纵横比 */
  margin-bottom: 50px; /* logo 与文字之间的间距 */
}

.welcome-text {
  font-size: 24px; /* 欢迎文字的大小 */
  font-weight: bold;
  color: #333; /* 文字颜色 */
}

@media (max-width: 600px) {
  .logo {
    width: 200px; /* 在小屏幕上调整 logo 的宽度 */
  }

  .welcome-text {
    font-size: 18px; /* 在小屏幕上调整文字大小 */
  }
}
</style>

