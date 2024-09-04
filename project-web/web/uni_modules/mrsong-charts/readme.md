# mrsong-charts

## 使用方法
```js
import mrsongCharts from '@/uni_modules/mrsong-charts/components/mrsong-charts/mrsong-charts.vue';
```

## 参数
```json
{
	"type":"line",//类型（必选）
	"title":"标题",//标题（非必选）
	"align":"left",//标题位置，left,center,right;（非必选）
	"options":{},//图表配置，与ucharts配置一样,自带默认配置（非必选）
	"config":{},//组件props,个人配置
	"unit":'人',//图表新增unit单位展示
	"chartsData":{
		"series": [{
			"data": [{
				"name": "一班",
				"value": 82
			}, {
				"name": "二班",
				"value": 63
			}, {
				"name": "三班",
				"value": 50
			}, {
				"name": "四班",
				"value": 40
			}, {
				"name": "五班",
				"value": 30
			}]
		}]
	},//图表数据，与ucharts配置一样（必选）
	// 注意：图表数据，与ucharts数据格式一样，不同图表，数据结构有差异
}
```
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
## 柱状图
```vue
<mrsongCharts type='column' title="柱状图" align='left' />
```

## 折线图
```vue
<mrsongCharts type='line' title="折线图" align='left' />
```

## 山峰图无边渐变色
```vue
<mrsongCharts type='mount' title="山峰图无边渐变色" align='left' />
```

## 圆角条状图+渐变色
```vue
<mrsongCharts type='pie' title="圆角条状图+渐变色" align='left' />
```

## 带分割线+渐变色
```vue
<mrsongCharts type='bar' title="带分割线+渐变色" align='left' />
```

## 环形图
```vue
<mrsongCharts type='ring' title="环形图" align='left' />
```

## 标准漏斗图
```vue
<mrsongCharts type='funnel' title="标准漏斗图" align='left' />
```