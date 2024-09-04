export function initColumnData(options) {
	return {
		"type": "column",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		"color": [
			"#008749",
			"#91CB74",
			"#FAC858",
			"#EE6666",
			"#73C0DE",
			"#3CA272",
			"#FC8452",
			"#9A60B4",
			"#ea7ccc"
		],
		"padding": [
			15,
			10,
			0,
			15
		],
		"rotate": false,
		"rotateLock": false,
		"fontSize": 13,
		"fontColor": "#666666",
		"enableScroll": true,
		"touchMoveLimit": 60,
		"enableMarkLine": false,
		"dataLabel": true,
		"dataPointShape": true,
		"dataPointShapeType": "solid",
		"xAxis": {
			"disabled": false,
			"axisLine": true,
			"axisLineColor": "#CCCCCC",
			"calibration": false,
			"fontColor": "#666666",
			"fontSize": 11,
			"rotateLabel": true,
			"itemCount": 4,
			"padding": 10,
			"margin": 10,
			"boundaryGap": "center",
			"disableGrid": true,
			"gridColor": "#CCCCCC",
			"gridType": "solid",
			"dashLength": 4,
			"gridEval": 1,
			"type": 'grid',
			"gridType": 'dash',
			"itemCount": 5, //x轴单屏显示数据的数量，默认为5个
			"scrollShow": false, //新增是否显示滚动条，默认false
			"scrollAlign": 'left', //滚动条初始位置
		},
		"yAxis": {
			"disabled": false,
			"disableGrid": false,
			"splitNumber": 4,
			"gridType": "dash",
			"dashLength": 2,
			"gridColor": "#CCCCCC",
			"padding": 10,
			"showTitle": false,
			"data": [{
				"type": "value",
				"position": "left",
				"disabled": false,
				"axisLine": true,
				"axisLineColor": "#CCCCCC",
				"calibration": false,
				"fontColor": "#666666",
				"fontSize": 13,
				"textAlign": "right",
				"title": "",
				"titleFontSize": 13,
				"titleOffsetY": 0,
				"titleOffsetX": 0,
				"titleFontColor": "#666666",
				"min": 0,
				"tofix": null,
				"unit": "",
				"format": "format1"
			}]
		},
		"legend": {
			"show": true,
			"position": "bottom",
			"float": "center",
			"padding": 5,
			"margin": 10,
			"backgroundColor": "rgba(0,0,0,0)",
			"borderColor": "rgba(0,0,0,0)",
			"borderWidth": 0,
			"fontSize": 13,
			"fontColor": "#666666",
			"lineHeight": 11,
			"hiddenColor": "#CECECE",
			"itemGap": 10
		},
		"extra": {
			"line": {
				"type": "straight",
				"width": 2
			},
			"tooltip": {
				"showBox": true,
				"showArrow": true,
				"borderWidth": 0,
				"borderRadius": 0,
				"borderColor": "#000000",
				"borderOpacity": 0.7,
				"bgColor": "#000000",
				"bgOpacity": 0.7,
				"gridType": "solid",
				"dashLength": 4,
				"gridColor": "#CCCCCC",
				"fontColor": "#FFFFFF",
				"splitLine": true,
				"horizentalLine": false,
				"xAxisLabel": false,
				"yAxisLabel": false,
				"labelBgColor": "#FFFFFF",
				"labelBgOpacity": 0.7,
				"labelFontColor": "#666666"
			},
			"markLine": {
				"type": "solid",
				"dashLength": 4,
				"data": []
			}
		}
	}
}
export function initLineData() {
	return {
		"type": "line",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		"color": [
			"#008749",
			"#91CB74",
			"#FAC858",
			"#EE6666",
			"#73C0DE",
			"#3CA272",
			"#FC8452",
			"#9A60B4",
			"#ea7ccc"
		],
		"padding": [
			15,
			10,
			0,
			15
		],
		"rotate": false,
		"rotateLock": false,
		"fontSize": 13,
		"fontColor": "#666666",
		"enableScroll": false,
		"touchMoveLimit": 60,
		"enableMarkLine": false,
		"dataLabel": true,
		"dataPointShape": true,
		"dataPointShapeType": "solid",
		"xAxis": {
			"disabled": false,
			"axisLine": true,
			"axisLineColor": "#CCCCCC",
			"calibration": false,
			"fontColor": "#666666",
			"fontSize": 10,
			"rotateLabel": true,
			"boundaryGap": "center",
			"disableGrid": true,
			"gridColor": "#CCCCCC",
			"gridType": "solid",
			"dashLength": 4,
			"gridEval": 1,
			"type": 'grid',
			"gridType": 'dash',
			"itemCount": 30, //x轴单屏显示数据的数量，默认为5个
			"scrollShow": true, //新增是否显示滚动条，默认false
			"scrollAlign": 'left', //滚动条初始位置
		},
		"yAxis": {
			"disabled": false,
			"disableGrid": false,
			"splitNumber": 5,
			"gridType": "dash",
			"dashLength": 2,
			"gridColor": "#CCCCCC",
			"padding": 10,
			"showTitle": false,
			"data": []
		},
		"legend": {
			"show": true,
			"position": "bottom",
			"float": "center",
			"padding": 5,
			"margin": 5,
			"backgroundColor": "rgba(0,0,0,0)",
			"borderColor": "rgba(0,0,0,0)",
			"borderWidth": 0,
			"fontSize": 13,
			"fontColor": "#666666",
			"lineHeight": 20,
			"hiddenColor": "#CECECE",
			"itemGap": 10
		},
		"extra": {
			"line": {
				"type": "straight",
				"width": 2
			},
			"tooltip": {
				"showBox": true,
				"showArrow": true,
				"borderWidth": 0,
				"borderRadius": 0,
				"borderColor": "#000000",
				"borderOpacity": 0.7,
				"bgColor": "#000000",
				"bgOpacity": 0.7,
				"gridType": "solid",
				"dashLength": 4,
				"gridColor": "#CCCCCC",
				"fontColor": "#FFFFFF",
				"splitLine": true,
				"horizentalLine": false,
				"xAxisLabel": false,
				"yAxisLabel": false,
				"labelBgColor": "#FFFFFF",
				"labelBgOpacity": 0.7,
				"labelFontColor": "#666666"
			},
			"markLine": {
				"type": "solid",
				"dashLength": 4,
				"data": []
			}
		}
	}
}
export function initFunnelData() {
	return {
		"type": "funnel",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		"color": [
			"#008749",
			"#91CB74",
			"#FAC858",
			"#EE6666",
			"#73C0DE",
			"#3CA272",
			"#FC8452",
			"#9A60B4",
			"#ea7ccc"
		],
		"padding": [
			15,
			15,
			0,
			15
		],
		"rotate": false,
		"rotateLock": false,
		"fontSize": 13,
		"fontColor": "#666666",
		"enableScroll": false,
		"touchMoveLimit": 60,
		"enableMarkLine": false,
		"dataLabel": true,
		"dataPointShape": true,
		"dataPointShapeType": "solid",
		"legend": {
			"show": true,
			"position": "bottom",
			"float": "center",
			"padding": 5,
			"margin": 0,
			"backgroundColor": "rgba(0,0,0,0)",
			"borderColor": "rgba(0,0,0,0)",
			"borderWidth": 0,
			"fontSize": 13,
			"fontColor": "#666666",
			"lineHeight": 20,
			"hiddenColor": "#CECECE",
			"itemGap": 10
		},
		"extra": {
			"funnel": {
				"activeOpacity": 0.3,
				"activeWidth": 10,
				"border": true,
				"borderWidth": 2,
				"borderColor": "#FFFFFF",
				"fillOpacity": 1,
				"labelAlign": "right",
				"linearType": "custom"
			},
			"tooltip": {
				"showBox": true,
				"showArrow": true,
				"borderWidth": 0,
				"borderRadius": 0,
				"borderColor": "#000000",
				"borderOpacity": 0.7,
				"bgColor": "#000000",
				"bgOpacity": 0.7,
				"gridType": "solid",
				"dashLength": 4,
				"gridColor": "#CCCCCC",
				"fontColor": "#FFFFFF",
				"splitLine": true,
				"horizentalLine": false,
				"xAxisLabel": false,
				"yAxisLabel": false,
				"labelBgColor": "#FFFFFF",
				"labelBgOpacity": 0.7,
				"labelFontColor": "#666666"
			}
		}
	}
}
export function initRingData() {
	return {
		"type": "ring",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		"color": [
			"#008749",
			"#91CB74",
			"#FAC858",
			"#EE6666",
			"#73C0DE",
			"#3CA272",
			"#FC8452",
			"#9A60B4",
			"#ea7ccc"
		],
		"padding": [
			5,
			5,
			5,
			5
		],
		"rotate": false,
		"errorReload": true,
		"fontSize": 13,
		"fontColor": "#666666",
		"enableScroll": false,
		"touchMoveLimit": 60,
		"enableMarkLine": false,
		"dataLabel": true,
		"dataPointShape": true,
		"dataPointShapeType": "solid",
		"tapLegend": true,
		"legend": {
			"show": true,
			"position": "bottom",
			"float": "center",
			"padding": 5,
			"margin": 5,
			"backgroundColor": "rgba(0,0,0,0)",
			"borderColor": "rgba(0,0,0,0)",
			"borderWidth": 0,
			"fontSize": 12,
			"fontColor": "#666666",
			"lineHeight": 25,
			"hiddenColor": "#CECECE",
			"itemGap": 10,
			"format": function(res) {
				console.log(res)
			}
		},
		"title": {
			"name": "",
			"fontSize": 15,
			"color": "#666666",
			"offsetX": 0,
			"offsetY": 0
		},
		"subtitle": {
			"name": "",
			"fontSize": 25,
			"color": "#7cb5ec",
			"offsetX": 0,
			"offsetY": 0
		},
		"extra": {
			"ring": {
				"ringWidth": 30,
				"centerColor": "#FFFFFF",
				"activeOpacity": 0.5,
				"activeRadius": 10,
				"offsetAngle": 0,
				"customRadius": 0,
				"labelWidth": 15,
				"border": true,
				"borderWidth": 3,
				"borderColor": "#FFFFFF",
				"linearType": "custom"
			},
			"tooltip": {
				"showBox": true,
				"showArrow": true,
				"showCategory": false,
				"borderWidth": 0,
				"borderRadius": 0,
				"borderColor": "#000000",
				"borderOpacity": 0.7,
				"bgColor": "#000000",
				"bgOpacity": 0.7,
				"gridType": "solid",
				"dashLength": 4,
				"gridColor": "#CCCCCC",
				"fontColor": "#FFFFFF",
				"splitLine": true,
				"horizentalLine": false,
				"xAxisLabel": false,
				"yAxisLabel": false,
				"labelBgColor": "#FFFFFF",
				"labelBgOpacity": 0.7,
				"labelFontColor": "#666666"
			}
		}
	}
}
export function initMountData() {
	return {
		"type": "mount",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		"color": ["#1890FF", "#91CB74", "#FAC858", "#EE6666", "#73C0DE", "#3CA272", "#FC8452", "#9A60B4", "#ea7ccc"],
		"padding": [15, 15, 0, 5],
		"legend": {},
		"xAxis": {
			"disableGrid": true
		},
		"yAxis": {
			"data": [{
				"min": 0
			}]
		},
		"extra": {
			"mount": {
				"type": "mount",
				"widthRatio": 1.5,
				"borderWidth": 0,
				"linearType": "custom"
			}
		}
	}
}
export function initBarData() {
	return {
		"type": "bar",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		color: ["#1890FF", "#91CB74", "#FAC858", "#EE6666", "#73C0DE", "#3CA272", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: [15, 30, 0, 5],
		legend: {},
		xAxis: {
			boundaryGap: "justify",
			disableGrid: false,
			min: 0,
			axisLine: false,
			max: 40
		},
		yAxis: {},
		extra: {
			bar: {
				type: "group",
				width: 30,
				meterBorde: 1,
				meterFillColor: "#FFFFFF",
				activeBgColor: "#000000",
				activeBgOpacity: 0.08,
				linearType: "custom",
				barBorderCircle: true,
				seriesGap: 2,
				categoryGap: 2
			}
		}
	}
}
export function initPieData() {
	return {
		"type": "pie",
		"canvasId": "",
		"canvas2d": false,
		"background": "none",
		"animation": true,
		"timing": "easeOut",
		"duration": 1000,
		color: ["#1890FF", "#91CB74", "#FAC858", "#EE6666", "#73C0DE", "#3CA272", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: [5, 5, 5, 5],
		extra: {
			pie: {
				activeOpacity: 0.5,
				activeRadius: 10,
				offsetAngle: 0,
				labelWidth: 15,
				border: true,
				borderWidth: 3,
				borderColor: "#FFFFFF",
				linearType: "custom"
			}
		}
	}
}
