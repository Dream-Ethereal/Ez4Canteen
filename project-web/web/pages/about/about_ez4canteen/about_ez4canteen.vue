<template>
	<view class="container">
		<!-- New Page Title -->
		<view class="page-title-container">
			<text class="page-title">关于Ez4Canteen</text>
		</view>

		<!-- About Ez4Canteen Section -->
		<view class="section">
			<text class="title">About Ez4Canteen（Easy for Canteen）</text>
			<text class="section-content">
				<text class="author">Author: Ethereal</text>
			</text>
			<text class="section-content">
				<text class="date">Date: 2024.8.24</text>
			</text>
		</view>
		
		<!-- 功能介绍 Section -->
		<view class="section">
			<text class="section-title">功能介绍</text>
			<text class="section-content">
				Ez4Canteen，是一个完全开源的项目。该项目主要面向的人群是线下餐饮店，使用方法如下：就餐人员可以通过扫码的方式，打开Ez4Canteen小程序端进行登录或者注册之后，可以进行点餐，在选择好菜品下单之后，在小程序端生成订单信息，上传到数据库之中，随后连接阿里云物联网平台，通过MQTT进行通信，将部分订单信息推送至主题之中，服务器通过云产品流转的方式，将该主题收到的信息转发给ESP8266所订阅的主题。ESP8266通过串口连接在STM32F103ZET6上，在收到信息之后，通过串口发送给STM32F103ZET6。开发板接收到串口的信息之后，通过串口外接的EM5820嵌入式热敏打印机模块，按照票据模板进行打印。
			</text>
			<text class="section-content">
				Ez4Canteen-Web端，是一个后台管理系统，只允许管理员登录。可以实现管理商品的上架/下架、编辑商品的信息、编辑/创建商品大类、使用uni统计查看流水情况、导出财务报表等功能。
			</text>
			<text class="section-content">
				更多详情，可以前往README文档查看。
			</text>
		</view>

		

		<!-- Github Section -->
		<view class="section">
			<text class="section-title">Github</text>
			<text class="section-content">【补上链接】</text>
		</view>
		
		<!-- Image Section -->
		<view class="image-section">
			<image class="section-image" src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/logo.png" alt="描述图片"></image>
			<view class="image-title-container">
				<text class="image-title">Ez4Canteen by Ethereal</text>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {}
		},
		methods: {}
	}
</script>

<style>
	.container {
		padding: 20px;
		font-family: Arial, sans-serif;
	}

	.page-title-container {
		display: flex;
		flex-direction: column;
		align-items: center; /* Center horizontally */
		margin-bottom: 20px; /* Space below the title */
	}

	.page-title {
		font-size: 36px; /* Increased font size for the page title */
		font-weight: bold;
		text-align: center; /* Ensure the text is centered within its container */
		position: relative; /* Needed for the pseudo-element positioning */
	}

	.page-title::after {
		content: ""; /* Required to display the border */
		display: block;
		width: 50%; /* Width of the line */
		height: 2px; /* Thickness of the line */
		background-color: #ccc; /* Color of the line */
		position: absolute;
		bottom: -10px; /* Position below the title with some space */
		left: 50%;
		transform: translateX(-50%); /* Center the line horizontally */
	}

	.section {
		margin-bottom: 30px; /* Increased margin to separate sections more clearly */
	}

	.title, .author, .date {
		display: block; /* Ensures each element is on its own line */
		margin-bottom: 10px;
	}

	.title {
		font-size: 28px; /* Increased font size for the title */
		font-weight: bold;
	}

	.author, .date {
		font-size: 18px; /* Increased font size for author and date */
		color: #666;
	}

	.section-title {
		font-size: 24px; /* Increased font size for section titles */
		font-weight: bold;
		margin-bottom: 10px;
		border-bottom: 1px solid #ccc;
		padding-bottom: 5px;
		display: block; /* Ensures the section title is on its own line */
	}

	.section-content {
		font-size: 18px; /* Increased font size for section content */
		line-height: 1.6; /* Increased line height for better readability */
		text-indent: 2em; /* Indent the first line of each paragraph by 2em */
		display: block; /* Ensures the section content is on its own line */
	}

	.image-section {
		text-align: center; /* Center the image container */
		margin-top: 40px; /* Space above the image section */
		position: relative; /* Positioning for the title */
	}

	.section-image {
		max-width: 200px; /* Ensure the image does not exceed the container width */
		height: 200px; /* Maintain aspect ratio */
	}

	.image-title-container {
		margin-top: 10px; /* Space between image and title */
	}

	.image-title {
		font-size: 16px; /* Font size for the image title */
		font-weight: bold;
	}
</style>
