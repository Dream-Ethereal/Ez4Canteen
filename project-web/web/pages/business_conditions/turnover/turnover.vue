<template>
  <view class="container">
    <view class="filter-container">
      <view class="date-filters">
        <span class="label">请选择：</span>
        <div class="buttons-wrapper">
          <button
            v-for="option in dateOptions"
            :key="option.value"
            @click="onDateOptionChange(option.value)"
            :class="{
              'active': selectedDateOption === option.value,
              'inactive': selectedDateOption !== option.value
            }"
          >
            {{ option.label }}
          </button>
        </div>
      </view>
      <view class="type-filters">
        <span class="label">请选择：</span>
        <div class="buttons-wrapper">
          <button
            v-for="option in typeOptions"
            :key="option.value"
            @click="onTypeOptionChange(option.value)"
            :class="{
              'active': selectedTypeOption === option.value,
              'inactive': selectedTypeOption !== option.value
            }"
          >
            {{ option.label }}
          </button>
        </div>
      </view>
    </view>

    <hr class="divider" />

    <view class="chart-title">{{ chartTitle }}</view>

    <view class="charts-box">
      <qiun-data-charts 
        :type="chartType"
        :opts="opts"
        :chartData="chartData"
      />
    </view>
  </view>
</template>

<script>
export default {
  data() {
    return {
      selectedDateOption: 'today',
      selectedTypeOption: 'expense',
      chartData: {},
      chartType: 'mount', 
	  Min: 0,
	  Max: 0,
      dateOptions: [
        { label: '今天', value: 'today' },
        { label: '昨天', value: 'yesterday' },
        { label: '近一周', value: 'week' },
        { label: '当月', value: 'month' },
        { label: '当年', value: 'year' }
      ],
      typeOptions: [
        { label: '支出', value: 'expense' },
        { label: '收入', value: 'income' },
        { label: '收支总计', value: 'total' }
      ],
      opts: {
        color: ["#1890FF","#91CB74","#FAC858","#EE6666","#73C0DE","#3CA272","#FC8452","#9A60B4","#ea7ccc","#FC1452","#42e854","#ae5410"],
        padding: [15,15,0,5],
        enableScroll: false,
        legend: {},
        xAxis: {
          disableGrid: true
        },
        yAxis: {
          data: [{ min: this.Min - 1000,  max: this.Max + 1000}]
        },
        extra: {
			  mount: {
			  type: "mount",
			  widthRatio: 1.5
			},
			 column: {
				type: "group",
				width: 30,
				activeBgColor: "#000000",
				activeBgOpacity: 0.08,
				linearType: "custom",
				seriesGap: 5,
				linearOpacity: 0.5,
				barBorderCircle: true,
				customColor: [
				  "#FA7D8D",
				  "#EB88E2"
				]
			}
        }
      }
    };
  },
   computed: {
      chartTitle() {
        switch (this.selectedTypeOption) {
          case 'income':
            return '收入情况统计图';
          case 'expense':
            return '支出情况统计图';
          case 'total':
            return '总收入/支出情况统计图';
          default:
            return '';
        }
      }
    },
  methods: {
	// 格式化时间为字符串格式 (例如：'2024-08-25 00:00:00')
    formatDateTime(date) {
      let year = date.getFullYear();
      let month = (date.getMonth() + 1).toString().padStart(2, '0');
      let day = date.getDate().toString().padStart(2, '0');
      let hours = date.getHours().toString().padStart(2, '0');
      let minutes = date.getMinutes().toString().padStart(2, '0');
      let seconds = date.getSeconds().toString().padStart(2, '0');
      return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    },
    async onDateOptionChange(value) {
      this.selectedDateOption = value;
      this.fetchChartData();
    },
    async onTypeOptionChange(value) {
      this.selectedTypeOption = value;
      this.fetchChartData();
    },
    async fetchChartData() {
         if (this.selectedTypeOption === 'expense') {
                this.chartType = 'mount';
                let res = {
                  series: [
                    {
                      data: []
                    }
                  ]
                };
        
                let startTime, endTime;
        
                if (this.selectedDateOption === 'today') {
                  // 今天
                  let todayStart = new Date();
                  todayStart.setHours(0, 0, 0, 0);
                  let todayEnd = new Date();
                  todayEnd.setHours(23, 59, 59, 999);
        
                  startTime = this.formatDateTime(todayStart);
                  endTime = this.formatDateTime(todayEnd);
        
                } else if (this.selectedDateOption === 'yesterday') {
                  // 昨天
                  let yesterdayStart = new Date();
                  yesterdayStart.setDate(yesterdayStart.getDate() - 1);
                  yesterdayStart.setHours(0, 0, 0, 0);
                  let yesterdayEnd = new Date();
                  yesterdayEnd.setDate(yesterdayEnd.getDate() - 1);
                  yesterdayEnd.setHours(23, 59, 59, 999);
        
                  startTime = this.formatDateTime(yesterdayStart);
                  endTime = this.formatDateTime(yesterdayEnd);
        
                } else if (this.selectedDateOption === 'week') {
                  // 一周
                  let weekStart = new Date();
                  weekStart.setDate(weekStart.getDate() - 6);
                  weekStart.setHours(0, 0, 0, 0);
                  let weekEnd = new Date();
                  weekEnd.setHours(23, 59, 59, 999);
        
                  startTime = this.formatDateTime(weekStart);
                  endTime = this.formatDateTime(weekEnd);
        
                } else if (this.selectedDateOption === 'month') {
                  // 一个月
                  let monthStart = new Date();
                  monthStart.setDate(1);
                  monthStart.setHours(0, 0, 0, 0);
                  let monthEnd = new Date();
                  monthEnd.setMonth(monthEnd.getMonth() + 1);
                  monthEnd.setDate(0);
                  monthEnd.setHours(23, 59, 59, 999);
        
                  startTime = this.formatDateTime(monthStart);
                  endTime = this.formatDateTime(monthEnd);
        
                } else if (this.selectedDateOption === 'year') {
                  // 一年
                  let yearStart = new Date();
                  yearStart.setMonth(0, 1);
                  yearStart.setHours(0, 0, 0, 0);
                  let yearEnd = new Date();
                  yearEnd.setMonth(11, 31);
                  yearEnd.setHours(23, 59, 59, 999);
        
                  startTime = this.formatDateTime(yearStart);
                  endTime = this.formatDateTime(yearEnd);
                }
        
                console.log('Start Time:', startTime, 'End Time:', endTime); // 打印时间戳用于调试
        
                let query = {
                  time: {
                    $gte: startTime, // 使用字符串进行比较
                    $lte: endTime
                  }
                };
        
                console.log('查询条件:', query); // 打印查询条件用于调试
        
                // 获取数据库数据并处理
                this.fetchData('expenditures', query).then(records => {
                  let data = [];
                  let groupedData = [];
        
                if (this.selectedDateOption === 'today' || this.selectedDateOption === 'yesterday') {
                    // 每两个小时
                    let biHourlyData = Array(12).fill(0);
        
                    records.forEach(record => {
                      let recordTime = new Date(record.time);
                      let hour = recordTime.getHours();
                      let index = Math.floor(hour / 2); // 将时间按2小时分组
                      biHourlyData[index] += parseFloat(record.amount); // 确保amount是数值类型
                    });
        
                    for (let i = 0; i < 12; i++) {
                      let startHour = i * 2;
                      let endHour = startHour + 2;
                      let startLabel = startHour < 10 ? `0${startHour}:00` : `${startHour}:00`;
                      let endLabel = endHour < 10 ? `0${endHour}:00` : `${endHour}:00`;
        
                      data.push({
                        name: `${startLabel}-${endLabel}`,
                        value: biHourlyData[i]
                      });
                    }
					res.series[0].data = data;
					this.chartData = JSON.parse(JSON.stringify(res));
        
                } else if (this.selectedDateOption === 'week') {
                    // 每天
                    let dailyData = Array(7).fill(0);
        
                    records.forEach(record => {
                      let recordTime = new Date(record.time);
                      let day = Math.floor((recordTime - new Date(startTime)) / (24 * 60 * 60 * 1000));
                      dailyData[day] += parseFloat(record.amount); // 确保amount是数值类型
                    });
					console.log(startTime);
					console.log(endTime);
                    for (let i = 0; i < 7; i++) {
                      // 计算当前日期
                      let currentDate = new Date(new Date(startTime).getTime() + i * 24 * 60 * 60 * 1000);
                    
                      // 格式化日期为MM-DD
                      let month = (currentDate.getMonth() + 1).toString().padStart(2, '0');
                      let day = currentDate.getDate().toString().padStart(2, '0');
                      let dateLabel = `${month}-${day}`;
                    
                      // 将数据添加到data数组中
                      data.push({
                        name: dateLabel,
                        value: dailyData[i]
                      });
                    }
					res.series[0].data = data;
					this.chartData = JSON.parse(JSON.stringify(res));
        
                } else if (this.selectedDateOption === 'month') {
					// 每周
					let weeklyData = Array(5).fill(0); // 增加一个数组位置用于处理最后一组

					records.forEach(record => {
						let recordTime = new Date(record.time);
						let day = recordTime.getDate();
						
						// 按天数分组
						let weekIndex;
						if (day <= 7) {
							weekIndex = 0;
						} else if (day <= 14) {
							weekIndex = 1;
						} else if (day <= 21) {
							weekIndex = 2;
						} else if (day <= 28) {
							weekIndex = 3;
						} else {
							weekIndex = 4; // 最后一组
						}
						
						weeklyData[weekIndex] += parseFloat(record.amount); // 确保amount是数值类型
					});

					// 获取当前月份
					let now = new Date();
					let month = (now.getMonth() + 1).toString().padStart(2, '0');
					let lastDayOfMonth = new Date(now.getFullYear(), now.getMonth() + 1, 0).getDate(); // 获取当前月份的最后一天
					
					// 计算每组的开始和结束日期
					let dateRanges = [
						{ start: '01', end: '07' },
						{ start: '08', end: '14' },
						{ start: '15', end: '21' },
						{ start: '22', end: '28' },
						{ start: `29`, end: `${lastDayOfMonth}` } // 处理最后一组
					];

					let data = [];
					
					dateRanges.forEach((range, index) => {
						let startLabel = `${month}-${range.start}`;
						let endLabel = index === 4 ? `${month}-${range.end}` : `${month}-${range.end}`;
						
						data.push({
							name: (`${startLabel}~${endLabel}`).toString(),
							value: weeklyData[index]
						});
					});
					// 打印数据用于调试
						console.log('Weekly Data:', weeklyData);
						console.log('Data for Chart:', data);

					res.series[0].data = data;
					this.chartData = JSON.parse(JSON.stringify(res));

						
					}else if (this.selectedDateOption === 'year') {
						// 每月
						
						let monthlyData = Array(12).fill(0);
			
						records.forEach(record => {
						  let recordTime = new Date(record.time);
						  let month = recordTime.getMonth();
						  monthlyData[month] += parseFloat(record.amount); // 确保amount是数值类型
						});
			
						for (let i = 0; i < 12; i++) {
						  let monthLabel = (i + 1).toString().padStart(2, '0') + '月';
						  data.push({
							name: monthLabel,
							value: monthlyData[i]
						  });
						}
						res.series[0].data = data;
						this.chartData = JSON.parse(JSON.stringify(res));
					}
					});
				} else if (this.selectedTypeOption === 'income') {
					  this.chartType = 'mount';
					  let res = {
						series: [
						  {
							data: []
						  }
						]
					  };

					  let startTime, endTime;

					  if (this.selectedDateOption === 'today') {
						// 获取今天的开始和结束时间
						let todayStart = new Date();
						todayStart.setHours(0, 0, 0, 0);
						let todayEnd = new Date();
						todayEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(todayStart);
						endTime = this.formatDateTime(todayEnd);

					  } else if (this.selectedDateOption === 'yesterday') {
						// 获取昨天的开始和结束时间
						let yesterdayStart = new Date();
						yesterdayStart.setDate(yesterdayStart.getDate() - 1);
						yesterdayStart.setHours(0, 0, 0, 0);
						let yesterdayEnd = new Date();
						yesterdayEnd.setDate(yesterdayEnd.getDate() - 1);
						yesterdayEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(yesterdayStart);
						endTime = this.formatDateTime(yesterdayEnd);

					  } else if (this.selectedDateOption === 'week') {
						// 获取本周的开始和结束时间
						let weekStart = new Date();
						weekStart.setDate(weekStart.getDate() - 6);
						weekStart.setHours(0, 0, 0, 0);
						let weekEnd = new Date();
						weekEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(weekStart);
						endTime = this.formatDateTime(weekEnd);

					  } else if (this.selectedDateOption === 'month') {
						// 获取本月的开始和结束时间
						let monthStart = new Date();
						monthStart.setDate(1);
						monthStart.setHours(0, 0, 0, 0);
						let monthEnd = new Date();
						monthEnd.setMonth(monthEnd.getMonth() + 1);
						monthEnd.setDate(0);
						monthEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(monthStart);
						endTime = this.formatDateTime(monthEnd);

					  } else if (this.selectedDateOption === 'year') {
						// 获取今年的开始和结束时间
						let yearStart = new Date();
						yearStart.setMonth(0, 1);
						yearStart.setHours(0, 0, 0, 0);
						let yearEnd = new Date();
						yearEnd.setMonth(11, 31);
						yearEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(yearStart);
						endTime = this.formatDateTime(yearEnd);
					  }

					  console.log('Start Time:', startTime, 'End Time:', endTime); // 打印时间戳用于调试

					  let query = {
						'orders.completed_time': {
						  $gte: startTime, // 使用字符串进行比较
						  $lte: endTime
						}
					  };

					  console.log('查询条件:', query); // 打印查询条件用于调试

					  // 获取数据库数据并处理
					  this.fetchData('user_info', query).then(records => {
						let data = [];
						let groupedData = [];

						records.forEach(record => {
						  record.orders.forEach(order => {
							let orderTime = new Date(order.completed_time);

							if (orderTime >= new Date(startTime) && orderTime <= new Date(endTime)) {
							  // 累加 order 的 amount 到相应的时间范围
							  if (this.selectedDateOption === 'today' || this.selectedDateOption === 'yesterday') {
								// 处理今天或昨天的数据，按每两个小时分组
								let hour = orderTime.getHours();
								let index = Math.floor(hour / 2); // 按2小时分组
								if (!groupedData[index]) groupedData[index] = 0;
								groupedData[index] += parseFloat(order.amount);

							  } else if (this.selectedDateOption === 'week') {
								// 处理一周的数据，按每天分组
								let day = Math.floor((orderTime - new Date(startTime)) / (24 * 60 * 60 * 1000));
								if (!groupedData[day]) groupedData[day] = 0;
								groupedData[day] += parseFloat(order.amount);

							  } else if (this.selectedDateOption === 'month') {
								// 处理每月的数据，按每周分组
								let day = orderTime.getDate();
								let weekIndex;
								if (day <= 7) {
								  weekIndex = 0;
								} else if (day <= 14) {
								  weekIndex = 1;
								} else if (day <= 21) {
								  weekIndex = 2;
								} else if (day <= 28) {
								  weekIndex = 3;
								} else {
								  weekIndex = 4; // 最后一组
								}
								if (!groupedData[weekIndex]) groupedData[weekIndex] = 0;
								groupedData[weekIndex] += parseFloat(order.amount);

							  } else if (this.selectedDateOption === 'year') {
								// 处理每年的数据，按每月分组
								let month = orderTime.getMonth();
								if (!groupedData[month]) groupedData[month] = 0;
								groupedData[month] += parseFloat(order.amount);
							  }
							}
						  });
						});

						// 构造图表数据
						if (this.selectedDateOption === 'today' || this.selectedDateOption === 'yesterday') {
						  for (let i = 0; i < 12; i++) {
							let startHour = i * 2;
							let endHour = startHour + 2;
							let startLabel = startHour < 10 ? `0${startHour}:00` : `${startHour}:00`;
							let endLabel = endHour < 10 ? `0${endHour}:00` : `${endHour}:00`;
							data.push({
							  name: `${startLabel}-${endLabel}`,
							  value: groupedData[i] || 0
							});
						  }

						} else if (this.selectedDateOption === 'week') {
						  for (let i = 0; i < 7; i++) {
							let currentDate = new Date(new Date(startTime).getTime() + i * 24 * 60 * 60 * 1000);
							let month = (currentDate.getMonth() + 1).toString().padStart(2, '0');
							let day = currentDate.getDate().toString().padStart(2, '0');
							let dateLabel = `${month}-${day}`;
							data.push({
							  name: dateLabel,
							  value: groupedData[i] || 0
							});
						  }

						} else if (this.selectedDateOption === 'month') {
						  let now = new Date();
						  let month = (now.getMonth() + 1).toString().padStart(2, '0');
						  let lastDayOfMonth = new Date(now.getFullYear(), now.getMonth() + 1, 0).getDate(); // 获取当前月份的最后一天
						  let dateRanges = [
							{ start: '01', end: '07' },
							{ start: '08', end: '14' },
							{ start: '15', end: '21' },
							{ start: '22', end: '28' },
							{ start: `29`, end: `${lastDayOfMonth}` }
						  ];
						  dateRanges.forEach((range, index) => {
							let startLabel = `${month}-${range.start}`;
							let endLabel = index === 4 ? `${month}-${range.end}` : `${month}-${range.end}`;
							data.push({
							  name: (`${startLabel}~${endLabel}`).toString(),
							  value: groupedData[index] || 0
							});
						  });

						} else if (this.selectedDateOption === 'year') {
						  for (let i = 0; i < 12; i++) {
							let monthLabel = (i + 1).toString().padStart(2, '0') + '月';
							data.push({
							  name: monthLabel,
							  value: groupedData[i] || 0
							});
						  }
						}

						res.series[0].data = data;
						this.chartData = JSON.parse(JSON.stringify(res));
					  });
					}
				else if (this.selectedTypeOption === 'total') {
					  this.chartType = 'mount';
					  let res = {
						series: [
						  {
							data: []
						  }
						]
					  };

					  let startTime, endTime;

					  if (this.selectedDateOption === 'today') {
						// 获取今天的开始和结束时间
						let todayStart = new Date();
						todayStart.setHours(0, 0, 0, 0);
						let todayEnd = new Date();
						todayEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(todayStart);
						endTime = this.formatDateTime(todayEnd);

					  } else if (this.selectedDateOption === 'yesterday') {
						// 获取昨天的开始和结束时间
						let yesterdayStart = new Date();
						yesterdayStart.setDate(yesterdayStart.getDate() - 1);
						yesterdayStart.setHours(0, 0, 0, 0);
						let yesterdayEnd = new Date();
						yesterdayEnd.setDate(yesterdayEnd.getDate() - 1);
						yesterdayEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(yesterdayStart);
						endTime = this.formatDateTime(yesterdayEnd);

					  } else if (this.selectedDateOption === 'week') {
						// 获取当前日期
						let today = new Date();
						// 计算当前日期的前七天
						let weekStart = new Date(today);
						weekStart.setDate(today.getDate() - 6); // 前七天的开始日期
						weekStart.setHours(0, 0, 0, 0);
						
						let weekEnd = new Date(today);
						weekEnd.setHours(23, 59, 59, 999); // 当前日期的结束时间

						startTime = this.formatDateTime(weekStart);
						endTime = this.formatDateTime(weekEnd);

					  } else if (this.selectedDateOption === 'month') {
						// 获取本月的开始和结束时间
						let monthStart = new Date();
						monthStart.setDate(1);
						monthStart.setHours(0, 0, 0, 0);
						let monthEnd = new Date();
						monthEnd.setMonth(monthEnd.getMonth() + 1);
						monthEnd.setDate(0);
						monthEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(monthStart);
						endTime = this.formatDateTime(monthEnd);


					  } else if (this.selectedDateOption === 'year') {
						// 获取当前年份的开始和结束时间
						let yearStart = new Date();
						yearStart.setMonth(0, 1);
						yearStart.setHours(0, 0, 0, 0);
						
						let yearEnd = new Date();
						yearEnd.setMonth(11, 31);
						yearEnd.setHours(23, 59, 59, 999);

						startTime = this.formatDateTime(yearStart);
						endTime = this.formatDateTime(yearEnd);
					  }

					  console.log('Start Time:', startTime, 'End Time:', endTime); // 打印时间戳用于调试

					  let expenseQuery = {
						time: {
						  $gte: startTime, // 使用字符串进行比较
						  $lte: endTime
						}
					  };

					  let incomeQuery = {
						'orders.completed_time': {
						  $gte: startTime, // 使用字符串进行比较
						  $lte: endTime
						}
					  };

					  // 获取支出数据
					  this.fetchData('expenditures', expenseQuery).then(expenseRecords => {
						// 获取收入数据
						this.fetchData('user_info', incomeQuery).then(incomeRecords => {
						  let groupedExpenseData;
						  let groupedIncomeData;
						  if (this.selectedDateOption === 'today' || this.selectedDateOption === 'yesterday') {
						          // 处理今天和昨天的数据，按每两个小时分组
						          groupedExpenseData = Array(12).fill(0); // 12个2小时分组
						          groupedIncomeData = Array(12).fill(0);
						  
						          expenseRecords.forEach(record => {
						            let recordTime = new Date(record.time);
						            if (recordTime >= new Date(startTime) && recordTime <= new Date(endTime)) {
						              let hour = recordTime.getHours();
						              let index = Math.floor(hour / 2); // 按2小时分组
						              groupedExpenseData[index] += parseFloat(record.amount);
						            }
						          });
						  
						          incomeRecords.forEach(record => {
						            record.orders.forEach(order => {
						              let orderTime = new Date(order.completed_time);
						              if (orderTime >= new Date(startTime) && orderTime <= new Date(endTime)) {
						                let hour = orderTime.getHours();
						                let index = Math.floor(hour / 2); // 按2小时分组
						                groupedIncomeData[index] += parseFloat(order.amount);
						              }
						            });
						          });
						  
						          // 构造图表数据
						          let data = [];
						          for (let i = 0; i < 12; i++) {
						            let startHour = i * 2;
						            let endHour = startHour + 2;
						            let startLabel = startHour < 10 ? `0${startHour}:00` : `${startHour}:00`;
						            let endLabel = endHour < 10 ? `0${endHour}:00` : `${endHour}:00`;
						            data.push({
						              name: `${startLabel}-${endLabel}`,
						              value: groupedIncomeData[i] - groupedExpenseData[i]
						            });
						          }
						  
						          res.series[0].data = data;
						          this.chartData = JSON.parse(JSON.stringify(res));
						  
						}else if(this.selectedDateOption === 'week') {
							groupedExpenseData = Array(7).fill(0); // 适用于一周的分组
							groupedIncomeData = Array(7).fill(0);

							// 处理支出数据
							expenseRecords.forEach(record => {
							  let recordTime = new Date(record.time);

							  if (recordTime >= new Date(startTime) && recordTime <= new Date(endTime)) {
								// 处理一周的数据，按每天分组
								let day = Math.floor((recordTime - new Date(startTime)) / (24 * 60 * 60 * 1000));
								groupedExpenseData[day] += parseFloat(record.amount);
							  }
							});

							// 处理收入数据
							incomeRecords.forEach(record => {
							  record.orders.forEach(order => {
								let orderTime = new Date(order.completed_time);

								if (orderTime >= new Date(startTime) && orderTime <= new Date(endTime)) {
								  // 处理一周的数据，按每天分组
								  let day = Math.floor((orderTime - new Date(startTime)) / (24 * 60 * 60 * 1000));
								  groupedIncomeData[day] += parseFloat(order.amount);
								}
							  });
							});

							// 构造图表数据
							let data = [];
							for (let i = 0; i < 7; i++) {
							  let currentDate = new Date(new Date(startTime).getTime() + i * 24 * 60 * 60 * 1000);
							  let month = (currentDate.getMonth() + 1).toString().padStart(2, '0');
							  let day = currentDate.getDate().toString().padStart(2, '0');
							  let nameLabel = `${month}-${day}`;

							  let value = groupedIncomeData[i] - groupedExpenseData[i];
							  data.push({
								name: nameLabel,
								value: value
							  });
							}

							res.series[0].data = data;
							this.chartData = JSON.parse(JSON.stringify(res));

						  } else if (this.selectedDateOption === 'month') {
							// 按每7天分组
							groupedExpenseData = [];
							groupedIncomeData = [];
							let startOfMonth = new Date(startTime);

							for (let i = 0; i < 5; i++) { // 最多5组（因为一个月最多有5个7天的周期）
							  let rangeStart = new Date(startOfMonth.getTime() + i * 7 * 24 * 60 * 60 * 1000);
							  let rangeEnd = new Date(rangeStart.getTime() + (7 * 24 * 60 * 60 - 1)* 1000);
							  if (rangeEnd > new Date(endTime)) rangeEnd = new Date(endTime); // 确保不超过当月最后一天
							  groupedExpenseData[i] = 0;
							  groupedIncomeData[i] = 0;

							  expenseRecords.forEach(record => {
								let recordTime = new Date(record.time);
								if (recordTime >= rangeStart && recordTime <= rangeEnd) {
								  groupedExpenseData[i] += parseFloat(record.amount);
								}
							  });

							  incomeRecords.forEach(record => {
								record.orders.forEach(order => {
								  let orderTime = new Date(order.completed_time);
								  if (orderTime >= rangeStart && orderTime <= rangeEnd) {
									groupedIncomeData[i] += parseFloat(order.amount);
								  }
								});
							  });
							}

							// 构造图表数据
							let data = [];
							for (let i = 0; i < groupedExpenseData.length; i++) {
							  let rangeStart = new Date(startOfMonth.getTime() + i * 7 * 24 * 60 * 60 * 1000);
							  let rangeEnd = new Date(rangeStart.getTime() + 6 * 24 * 60 * 60 * 1000);
							  if (rangeEnd > new Date(endTime)) rangeEnd = new Date(endTime); // 确保不超过当月最后一天

							  let startLabel = `${(rangeStart.getMonth() + 1).toString().padStart(2, '0')}-${rangeStart.getDate().toString().padStart(2, '0')}`;
							  let endLabel = `${(rangeEnd.getMonth() + 1).toString().padStart(2, '0')}-${rangeEnd.getDate().toString().padStart(2, '0')}`;
							  let nameLabel = `${startLabel}~${endLabel}`;
							  let value = groupedIncomeData[i] - groupedExpenseData[i];
							  data.push({
								name: nameLabel,
								value: value
							  });
							}

							res.series[0].data = data;
							this.chartData = JSON.parse(JSON.stringify(res));

						  } else if (this.selectedDateOption === 'year') {
							// 按每月分组
							groupedExpenseData = Array(12).fill(0);
							groupedIncomeData = Array(12).fill(0);

							expenseRecords.forEach(record => {
							  let recordTime = new Date(record.time);
							  let month = recordTime.getMonth();
							  if (recordTime >= new Date(startTime) && recordTime <= new Date(endTime)) {
								groupedExpenseData[month] += parseFloat(record.amount);
							  }
							});

							incomeRecords.forEach(record => {
							  record.orders.forEach(order => {
								let orderTime = new Date(order.completed_time);
								let month = orderTime.getMonth();
								if (orderTime >= new Date(startTime) && orderTime <= new Date(endTime)) {
								  groupedIncomeData[month] += parseFloat(order.amount);
								}
							  });
							});

							// 构造图表数据
							let data = [];
							for (let i = 0; i < 12; i++) {
							  let monthLabel = `${(i + 1).toString().padStart(2, '0')}月`;
							  let value = groupedIncomeData[i] - groupedExpenseData[i];
							  data.push({
								name: monthLabel,
								value: value
							  });
							}

							res.series[0].data = data;
							this.chartData = JSON.parse(JSON.stringify(res));
						  }
						});
					  });
					}

    },
	async fetchData(collectionName, query) {
	  const db = uniCloud.database();  // 获取数据库实例
	  const collection = db.collection(collectionName);  // 获取指定集合
	
	  try {
	    // 查询数据并返回结果
	    const result = await collection.where(query).get();
	    if (result && result.result.data) {
			console.log(result.result.data);
	      return result.result.data;
	    } else {
	      console.log('没有查询到数据');  // 打印空结果日志
	      return [];
	    }

	  } catch (error) {
	    console.error('数据库查询错误：', error);
	    return [];  // 查询失败时，返回空数组
	  }
	},
  },
  mounted() {
    this.fetchChartData(); // 初始加载数据
  }
};
</script>

<style scoped>
.container {
  padding: 20px;
}

.filter-container {
  display: flex;
  flex-direction: column;
  margin-bottom: 20px;
}

.date-filters,
.type-filters {
  display: flex;
  align-items: center;
  margin-bottom: 10px;
  justify-content: flex-start; /* 左对齐 */
}

.label {
  margin-right: 10px;
  font-size: 14px;
}

.buttons-wrapper {
  display: flex;
}

button {
  padding: 10px; /* 去除padding */
  background-color: transparent; /* 背景透明 */
  color: black;
  cursor: pointer;
  font-size: 16px;
  position: relative;
  margin-right: 20px; /* 按钮之间的间距 */
  border: none; /* 移除边框 */
  line-height: 20px;
}

button.active {
  color: green;
  font-size: 16px;
}

button.active::after {
  content: "";
  display: block;
  width: 0%; /* 横线与文字宽度一致 */
  height: 2px;
  background-color: green;
  position: absolute;
  bottom: -2px; /* 调整位置使其在文字正下方 */
  left: 0;
}

button.inactive {
  color: black;
  font-size: 16px;
}

button.inactive::after {
  content: "";
  display: block;
  width: 0%; /* 横线与文字宽度一致 */
  height: 1px;
  background-color: black;
  position: absolute;
  bottom: -10px; /* 调整位置使其在文字正下方 */
  left: 0;
}

.divider {
  border: 1px solid #ddd;
  margin-bottom: 20px;
}

.chart-title {
  text-align: center;
  font-size: 20px;
  font-weight: bold;
  margin-bottom: 10px;
}

.charts-box {
  width: 100%;
  height: 300px;
}
</style>