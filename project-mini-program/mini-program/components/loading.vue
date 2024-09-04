<template>
	<view class="loading">
		<image src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/logo.png"></image>
	</view>
</template>

<script>
	export default {
		name: 'Loading',
		data() {
			return {
				
			}
		}
	}
</script>

<style lang="scss">
	.loading {
		width: 100%;
		height: 100%;
		display: flex;
		align-items: center;
		justify-content: center;

		image {
			width: 260rpx;
			height: 260rpx;
			position: relative;
			margin-top: 200rpx;
		}
	}
</style>
