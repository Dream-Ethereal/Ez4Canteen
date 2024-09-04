<template>
	<view v-if="showChart" class="mrsong-charts">
		<view class="chart-title-box" :style="'text-align:' + align">
			<slot name="title">
				<text class="chart-title">{{ title }}</text>
			</slot>
		</view>
		<view class="charts-box">
			<slot name="unit">
				<view v-if="unit" class="chart-unit">单位：{{ unit ? `(${unit})` : '' }}</view>
			</slot>
			<qiun-data-charts :opts="opts" type="column" :chart-data="currentData" background="none" :animation="false" :ontouch="true" />
		</view>
	</view>
</template>
<script>
import { initColumnData, initLineData, initFunnelData, initRingData, initMountData, initBarData, initPieData } from './uchart.config.js';
import qiunDataCharts from './qiun-data-charts/components/qiun-data-charts/qiun-data-charts';
export default {
	name: 'MrsongCharts',
	components: {
		qiunDataCharts
	},
	props: {
		type: {
			type: String,
			default: 'column'
		},
		unit: {
			type: String,
			default: ''
		},
		chartsData: {
			type: Object,
			default() {
				return null;
			}
		},
		config: {
			type: Object,
			default() {
				return {
					itemCount: 3, // x轴单屏显示数据的数量，默认为5个
					scrollShow: false, // 新增是否显示滚动条，默认false
					scrollAlign: 'left', // 滚动条初始位置
					rotateLabel: true, // X轴label旋转
					min: 0, // Y轴最小值
					// "max": 150, //Y轴大值
					unit: '', // Y轴单位
					enableScroll: false, // 开启滚动模式
					color: [
						// 颜色设置
						'#9A60B4',
						'#ea7ccc'
					]
				};
			}
		},
		options: {
			type: Object,
			default() {
				return {
					color: ['#008749', '#91CB74', '#FAC858', '#EE6666', '#73C0DE', '#3CA272', '#FC8452', '#9A60B4', '#ea7ccc'],
					xAxis: {
						itemCount: 3, // x轴单屏显示数据的数量，默认为5个
						scrollShow: false, // 新增是否显示滚动条，默认false
						scrollAlign: 'left', // 滚动条初始位置
						rotateLabel: true // X轴label旋转
					},
					yAxis: {
						data: [
							{
								min: 0, // Y轴最小值
								// "max": 150, //Y轴大值
								unit: '' // Y轴单位
							}
						]
					},
					enableScroll: false // 开启滚动模式
				};
			}
		},
		title: {
			type: String,
			default: '标题'
		},
		align: {
			type: String,
			default: 'center'
		}
	},
	data() {
		return {
			opts: {},
			yMax: 10,
			currentData: {
				categories: [],
				series: []
			},
			showChart: false
		};
	},
	computed: {},
	watch: {
		type: {
			handler(val) {
				if (val) {
					this.formatType(val);
				}
			},
			deep: true,
			immediate: true
		},
		options: {
			handler(val) {
				if (val) {
					let opts = this.assignDeep(this.opts, val);
					if (this.config) {
						let xAxis = opts.xAxis;
						let yAxis = opts.yAxis.length ? opts.yAxis[0] : {};
						let color = this.config.color;
						if (opts.color) opts.color = color;
						for (let key in this.config) {
							if (Object.keys(xAxis).includes(key)) xAxis[key] = this.config[key];
							if (Object.keys(yAxis).includes(key)) yAxis[key] = this.config[key];
							if (Object.keys(opts).includes(key)) {
								opts[key] = this.config[key];
							}
						}
						this.opts = opts;
					}
				}
			},
			deep: true,
			immediate: true
		},
		chartsData: {
			handler(val) {
				if (val) {
					this.currentData = val;
					let list = [];
					let opts = {};
					let seriesItem = val.series || [];
					seriesItem.map((item) => {
						list = [...list, ...item.data];
					});
					if (this.type == 'column' || this.type == 'line') {
						let max = Math.max.apply(
							Math,
							list.map((item) => {
								return item;
							})
						);
						this.yMax = max > 10 ? max : 10;
						this.opts.yAxis.data.forEach((item) => {
							if (max > 10) {
								delete item.max;
							} else {
								item.max = this.yMax;
							}
						});
					}
				} else {
					this.currentData = this.initchartsData();
				}
			},
			deep: true,
			immediate: true
		}
	},
	mounted() {
		uni.showLoading({
			title: '正在加载'
		});
		this.$nextTick(() => {
			this.showChart = true;
			uni.hideLoading();
		});
	},
	methods: {
		initchartsData() {
			if (this.type == 'mount' || this.type == 'pie' || this.type == 'ring' || this.type == 'funnel') {
				return {
					series: [
						{
							data: [
								{
									name: '一班',
									value: 82
								},
								{
									name: '二班',
									value: 63
								},
								{
									name: '三班',
									value: 50
								},
								{
									name: '四班',
									value: 40
								},
								{
									name: '五班',
									value: 30
								}
							]
						}
					]
				};
			} else {
				return {
					categories: ['2016', '2017', '2018', '2019', '2020', '2021'],
					series: [
						{
							name: '目标值',
							data: [40, 36, 31, 33, 13, 34]
						},
						{
							name: '完成量',
							data: [18, 27, 21, 24, 6, 28]
						}
					]
				};
			}
		},
		assignDeep(target) {
			// 判断是否是纯粹对象
			const isPlainObject = (obj) => {
				return Object.prototype.toString.call(obj) === '[object Object]';
			};
			const args = Array.from(arguments);
			if (args.length < 2) return args[0];
			let result = args[0];
			args.shift();
			args.forEach((item) => {
				if (isPlainObject(item)) {
					if (!isPlainObject(result)) result = {};
					for (let key in item) {
						if (result[key] && isPlainObject(item[key])) {
							result[key] = this.assignDeep(result[key], item[key]);
						} else {
							result[key] = item[key];
						}
					}
				} else if (item instanceof Array) {
					if (!(result instanceof Array)) result = [];
					item.forEach((arrItem, arrIndex) => {
						if (isPlainObject(arrItem)) {
							result[arrIndex] = this.assignDeep(result[arrIndex]);
						} else {
							result[arrIndex] = arrItem;
						}
					});
				}
			});
			return result;
		},
		formatType(str) {
			switch (str) {
				case 'column':
					this.opts = initColumnData();
					break;
				case 'line':
					this.opts = initLineData();
					break;
				case 'funnel':
					this.opts = initFunnelData();
					break;
				case 'ring':
					this.opts = initRingData();
					break;
				case 'mount':
					this.opts = initMountData();
					break;
				case 'bar':
					this.opts = initBarData();
					break;
				case 'pie':
					this.opts = initPieData();
					break;
				default:
					break;
			}
		}
	}
};
</script>

<style lang="scss" scoped>
* {
	box-sizing: border-box;
}

.charts-box {
	width: 100%;
	height: 600rpx;
	padding: 50rpx 0;
	background: #fff;

	.chart-unit {
		width: 100%;
		display: flex;
		justify-content: flex-end;
		align-items: center;
		line-height: 80rpx;
		font-size: 28rpx;
	}
}

.chart-title-box,
.mrsong-charts {
	width: 100%;
	box-sizing: border-box;
}

.chart-title-box {
	font-size: 30rpx;
	color: '#666666';
	font-weight: 500;
	text-align: left;
}

.mrsong-charts {
	padding: 30rpx;
}
</style>
