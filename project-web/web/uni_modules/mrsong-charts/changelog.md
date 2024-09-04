## 1.0.8（2023-08-15）
## 新增slot布局
- 可自定义title布局
- 可自定unit布局
```vue
<template>
	<view class="content">
		<mrsongCharts type='column' title="柱状图" align='left'>
			<div slot="title" class="chart-title">测试slot自定义title</div>
			<div slot="unit" class="chart-unit">测试slot自定义unit</div>
		</mrsongCharts>
		<mrsongCharts type='line' title="折线图" align='left' />
		<mrsongCharts type='mount' title="山峰图无边渐变色" align='left' />
		<mrsongCharts type='pie' title="圆角条状图+渐变色" align='left' />
		<mrsongCharts type='bar' title="带分割线+渐变色" align='left' />
		<mrsongCharts type='ring' title="环形图" align='left' />
		<mrsongCharts type='funnel' title="标准漏斗图" align='left' />
	</view>
</template>
```

## 1.0.7（2023-08-15）
## 更新示例工程
## 1.0.6（2023-08-15）
## 更改组件样式表
## 1.0.5（2023-08-15）
## 修复小程序兼容问题
## 修复tooltip不显示问题
注意：包裹组件的元素不能出现定位，否则tooltip显示异常
## 1.0.4（2022-08-18）
## 修复bug
小程序语法兼容
## 1.0.3（2022-08-15）
## 新增个人配置
```json
// config:组件props,个人配置
{
	"itemCount": 3, //x轴单屏显示数据的数量，默认为5个
	"scrollShow": false, //新增是否显示滚动条，默认false
	"scrollAlign": 'left', //滚动条初始位置
	"rotateLabel": true, //X轴label旋转
	"min": 0, //Y轴最小值
	"max": 150, //Y轴大值
	"unit": "", //Y轴单位
	"enableScroll": false, //开启滚动模式
	"color": [//颜色设置
		"#9A60B4",
		"#ea7ccc"
	],
}
```
## 1.0.2（2022-08-02）
## 图表新增unit单位展示
## 1.0.1（2022-08-02）
修复bug
## 1.0.0（2022-08-02）
init
