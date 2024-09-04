<template>
  <view class="container">
    <!-- 标题 -->
    <view class="title">
      导出为Excel表格
    </view>
    <!-- 横线 -->
    <view class="divider"></view>
    <view class="title2">
      请填写下方导出配置！
    </view>
    <!-- 表单 -->
    <form class="form">
      <!-- 快速选择 -->
      <view class="form-item">
        <label for="quick-select">快速选择：</label>
        <select v-model="quickSelect" @change="updateDateRange" class="select-box">
          <option value="custom">自定义</option>
          <option value="today">今天</option>
          <option value="yesterday">昨天</option>
          <option value="lastWeek">近一周</option>
          <option value="currentMonth">当月</option>
          <option value="currentYear">当年</option>
        </select>
      </view>

      <!-- 时间范围 -->
      <view class="form-item">
        <label>时间：</label>
        <view class="date-picker-container">
          <uni-datetime-picker
            mode="datetime"
            :start="startDate"
            :end="endDate"
            :value="dateRange.start"
            @change="handleDateChange('start', $event)"
            :disabled="quickSelect !== 'custom'"
            class="date-picker"
          />
          <text class="separator"> —</text>
          <uni-datetime-picker
            mode="datetime"
            :start="startDate"
            :end="endDate"
            :value="dateRange.end"
            @change="handleDateChange('end', $event)"
            :disabled="quickSelect !== 'custom'"
            class="date-picker"
          />
        </view>
      </view>

      <!-- 导出类型 -->
      <view class="form-item">
        <label>导出类型：</label>
        <view class="export-options">
          <button
            v-for="(type, index) in exportTypes"
            :key="index"
            :class="['export-option', { 'active': exportType === type.value }]"
            @click="exportType = type.value"
          >
            {{ type.label }}
          </button>
        </view>
      </view>

      <!-- 开始导出按钮 -->
      <view class="form-item">
        <button class="export-button" @click="exportData">开始导出</button>
      </view>
    </form>
    
    <!-- 横线 -->
    <view class="divider2"></view>
    
    <view class="welcome-container">
      <image class="logo" src="https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/logo.png" /> <!-- 替换为实际的 logo 图片路径 -->
      <view class="welcome-text">
        Ez4Canteen by Ethereal
      </view>
    </view>
  </view>
</template>

<script>
import uniDatetimePicker from '@dcloudio/uni-ui/lib/uni-datetime-picker/uni-datetime-picker.vue'; // Import the datetime picker component
import * as XLSX from 'xlsx'; // Import all members from xlsx

export default {
  components: {
    uniDatetimePicker
  },
  data() {
    return {
      quickSelect: 'custom',
      dateRange: {
        start: '',
        end: ''
      },
      exportType: 'income',
      exportTypes: [
        { value: 'income', label: '导出收入报表' },
        { value: 'expense', label: '导出支出报表' },
        { value: 'both', label: '导出收入/支出报表' }
      ],
      startDate: '2000-01-01 00:00:00',
      endDate: '2099-12-31 23:59:59'
    };
  },
  methods: {
    updateDateRange() {
      const now = new Date();
      let startDate;
      let endDate;
      switch (this.quickSelect) {
        case 'today':
          startDate = new Date(now.getFullYear(), now.getMonth(), now.getDate(), 0, 0, 0);
          endDate = new Date(now.getFullYear(), now.getMonth(), now.getDate(), 23, 59, 59);
          break;
        case 'yesterday':
          startDate = new Date(now.getFullYear(), now.getMonth(), now.getDate() - 1, 0, 0, 0);
          endDate = new Date(now.getFullYear(), now.getMonth(), now.getDate() - 1, 23, 59, 59);
          break;
        case 'lastWeek':
          endDate = new Date(now);
          endDate.setHours(23, 59, 59, 999); 
          const startOfWeek = new Date(now);
          startOfWeek.setDate(now.getDate() - 6); 
          startDate = new Date(startOfWeek);
          startDate.setHours(0, 0, 0, 0);
          break;
        case 'currentMonth':
          startDate = new Date(now.getFullYear(), now.getMonth(), 1, 0, 0, 0);
          endDate = new Date(now.getFullYear(), now.getMonth() + 1, 0, 23, 59, 59);
          break;
        case 'currentYear':
          startDate = new Date(now.getFullYear(), 0, 1, 0, 0, 0);
          endDate = new Date(now.getFullYear(), 11, 31, 23, 59, 59);
          break;
        case 'custom':
        default:
          return;
      }
      this.dateRange.start = this.formatDateTime(startDate);
      this.dateRange.end = this.formatDateTime(endDate);
    },
    async exportData() {
            const { start, end } = this.dateRange;
            const startDate = new Date(start);
            const endDate = new Date(end);
            const diffDays = Math.ceil((endDate - startDate) / (1000 * 60 * 60 * 24));
            const reports = [];
        
            try {
                // Fetch data
                const userOrders = await this.fetchUserOrders(startDate, endDate);
                const expenditures = await this.fetchExpenditures(startDate, endDate);
        
                // 如果数据为空，弹出提示
                if (!userOrders.length && !expenditures.length) {
                    uni.showModal({
                        title: '提示',
                        content: '没有可导出的数据。',
                        showCancel: false,
                    });
                    return;
                }
        
                let combinedData = [];
        
                if (this.exportType === 'income' || this.exportType === 'both') {
                    combinedData = combinedData.concat(this.createIncomeReport(userOrders));
                }
        
                if (this.exportType === 'expense' || this.exportType === 'both') {
                    combinedData = combinedData.concat(this.createExpenseReport(expenditures));
                }
        
                // Sort by date and assign serial numbers
                combinedData.sort((a, b) => new Date(a.时间) - new Date(b.时间));
                combinedData = combinedData.map((item, index) => ({ ...item, 序号: index + 1 }));
        
                if (this.quickSelect === 'currentYear') {
                    const months = this.getMonthRange(startDate, endDate);
                    const wb = XLSX.utils.book_new();
        
                    // Create the total report
                    const totalSheetName = '总表';
                    const wsTotal = XLSX.utils.json_to_sheet(combinedData);
                    // this.addTotalRow(wsTotal, combinedData);
                    XLSX.utils.book_append_sheet(wb, wsTotal, totalSheetName);
        
                    // Create monthly reports
                    months.forEach((month) => {
                        const monthlyData = this.filterByMonth(combinedData, month);
                        if (monthlyData.length > 0) {
                            const sheetName = `${month} 数据`;
                            const wsMonthly = XLSX.utils.json_to_sheet(monthlyData);
                            // this.addTotalRow(wsMonthly, monthlyData);
                            XLSX.utils.book_append_sheet(wb, wsMonthly, sheetName);
                        }
                    });
        
                    // Generate the Excel file
                    this.generateAndDownloadExcel(wb, '年度报表');
                } else {
                    if (diffDays <= 31) {
                        const wb = XLSX.utils.book_new();
                        const sheetName = '总表';
                        const ws = XLSX.utils.json_to_sheet(combinedData);
                        // this.addTotalRow(ws, combinedData);
                        XLSX.utils.book_append_sheet(wb, ws, sheetName);
                        this.generateAndDownloadExcel(wb, 'CombinedReport');
                    } else {
                        const months = this.getMonthRange(startDate, endDate);
                        months.forEach((month) => {
                            const monthlyData = this.filterByMonth(combinedData, month);
                            if (monthlyData.length > 0) {
                                const wb = XLSX.utils.book_new();
                                const sheetName = `${month} 数据`;
                                const ws = XLSX.utils.json_to_sheet(monthlyData);
                                // this.addTotalRow(ws, monthlyData);
                                XLSX.utils.book_append_sheet(wb, ws, sheetName);
                                this.generateAndDownloadExcel(wb, `${month} Report`);
                            }
                        });
                    }
                }
            } catch (error) {
                console.error('导出数据时发生错误:', error);
            }
        },
    async fetchUserOrders(startDate, endDate) {
      try {
        const db = uniCloud.database();
        
        // 确保 startDate 和 endDate 是字符串格式，和数据库中的格式一致
        const formattedStartDate = this.formatDateTime(new Date(startDate));
        const formattedEndDate = this.formatDateTime(new Date(endDate));
    
        const res = await db.collection('user_info').where({
          'orders.completed_time': {
            $gte: formattedStartDate,
            $lte: formattedEndDate
          }
        }).get();
        
        
        // 提取订单数据
        const orders = res.result.data.flatMap(doc => doc.orders.filter(order => 
          order.completed_time >= formattedStartDate && order.completed_time <= formattedEndDate
        ));
    
        return orders;
      } catch (error) {
        console.error('Error fetching user orders:', error);
        return [];
      }
    },

    async fetchExpenditures(startDate, endDate) {
      try {
        const db = uniCloud.database();
        
        // 确保 startDate 和 endDate 是字符串格式，和数据库中的格式一致
        const formattedStartDate = this.formatDateTime(new Date(startDate));
        const formattedEndDate = this.formatDateTime(new Date(endDate));
        
        const res = await db.collection('expenditures').where({
          'time': {
            $gte: formattedStartDate,
            $lte: formattedEndDate
          }
        }).get();
        return res.result.data;
      } catch (error) {
        console.error('Error fetching expenditures:', error);
        return [];
      }
    },
    formatDateTime(date) {
      // 格式化为 "yyyy-MM-dd HH:mm:ss" 格式的字符串
      return `${date.getFullYear()}-${String(date.getMonth() + 1).padStart(2, '0')}-${String(date.getDate()).padStart(2, '0')} ${String(date.getHours()).padStart(2, '0')}:${String(date.getMinutes()).padStart(2, '0')}:${String(date.getSeconds()).padStart(2, '0')}`;
    },
    createIncomeReport(orders) {
      if (orders.length === 0) {
        console.warn('没有收入订单数据');
      }
      return orders.map((order, index) => ({
        序号: index + 1,
        编号: order.order_no || 'N/A',
        时间: order.completed_time || 'N/A',
        类型: '收入',
        金额: parseFloat(order.amount) || 0 // 确保金额是数字
      }));
    },
    
    createExpenseReport(expenditures) {
      if (expenditures.length === 0) {
        console.warn('没有支出数据');
      }
      return expenditures.map((expense, index) => ({
        序号: index + 1,
        编号: expense.id || 'N/A',
        时间: expense.time || 'N/A',
        类型: '支出',
        金额: (parseFloat(expense.amount) || 0) * -1 // 确保金额是负数
      }));
    },
    getMonthRange(startDate, endDate) {
      const months = [];
      const startMonth = startDate.getFullYear() * 12 + startDate.getMonth();
      const endMonth = endDate.getFullYear() * 12 + endDate.getMonth();

      for (let i = startMonth; i <= endMonth; i++) {
        const month = Math.floor(i % 12) + 1;
        const year = Math.floor(i / 12);
        months.push(`${year}-${String(month).padStart(2, '0')}`);
      }

      return months;
    },
    filterByMonth(report, month) {
      return report.filter(item => item.时间.startsWith(month));
    },
    generateAndDownloadExcel(workbook, fileName) {
      // Add totals to each sheet
      workbook.SheetNames.forEach(sheetName => {
        const ws = workbook.Sheets[sheetName];
        const data = XLSX.utils.sheet_to_json(ws, { header: 1 }); // Convert sheet to JSON
		this.addTotalRow(ws, data); // Add total row to each sheet
      });
    
      // Generate the Excel file
      const wbout = XLSX.write(workbook, { bookType: 'xlsx', type: 'array' });
    
      const blob = new Blob([wbout], { type: 'application/octet-stream' });
      const url = URL.createObjectURL(blob);
      const link = document.createElement('a');
      link.href = url;
      link.download = `${fileName} Ez4Canteen报表.xlsx`;
      link.click();
      URL.revokeObjectURL(url);
    },
    calculateTotal(data) {
      if (!data.length) return null;
      const total = data.reduce((sum, row) => sum + (parseFloat(row.金额) || 0), 0);
      return ['总计', '', '', '', total];
    },
	addTotalRow(ws, data) {
	        if (!data.length) return;
	    
	        const amountColumnIndex = 4; // Assuming the '金额' column is the 5th column (index 4)
	    
	        
	    
	        // Calculate the total amount
	        const totalAmount = data.slice(1).reduce((sum, row) => sum + (parseFloat(row[amountColumnIndex]) || 0), 0);

	        const totalRow = [`总计`, '', '', '', totalAmount]; // Adjust if necessary to match the sheet structure
	    
	        // Write the total row to the worksheet
	        XLSX.utils.sheet_add_aoa(ws, [totalRow], { origin: -1 });
	    },
	}
  }
</script>

<style scoped>
.container {
  display: flex;
  flex-direction: column;
  align-items: center;
  padding: 20px;
}

.title {
  font-size: 42px;
  font-weight: bold;
  margin-bottom: 10px;
}

.title2 {
  font-size: 24px;
  font-weight: bold;
  margin-bottom: 50px;
}

.divider {
  width: 100%;
  height: 1px;
  background-color: #ccc;
  margin-bottom: 20px;
}

.divider2 {
  width: 100%;
  height: 1px;
  background-color: #ccc;
  margin-bottom: 20px;
  margin-top: 80px;
}

.form {
  display: flex;
  flex-direction: column;
  width: 100%;
  max-width: 600px;
}

.form-item {
  display: flex;
  align-items: center;
  margin-bottom: 15px;
}

label {
  width: 150px;
  font-weight: bold;
}

.select-box {
  padding: 5px;
  border: 1px solid #ccc;
  border-radius: 4px;
  width: 300px; /* 拉宽下拉框宽度 */
  height: 36px; /* 高度与其他组件一致 */
}

.date-picker-container {
  display: flex;
  align-items: center;
}

.date-picker {
  flex: 1;
}

.date-picker .uni-datetime-picker {
  background-color: #fff;
  border: 1px solid #ccc;
}

.date-picker[disabled] {
  background-color: #eaeaea; /* 背景颜色灰色表示不可修改 */
}

.separator {
  margin-left: 10px;
  margin-right: 10px;
  font-size: 18px;
}

.export-options {
  display: flex;
  width: 100%;
  flex-direction: row;
}

.export-option {
  flex: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-right: 10px;
  padding: 6px 12px; /* 调整按钮的内边距 */
  border: 1px solid green;
  border-radius: 4px;
  cursor: pointer;
  background-color: #fff;
  color: green;
  font-size: 14px; /* 调整字体大小 */
}

.export-option.active {
  background-color: green;
  color: #fff;
}

.export-button {
  width: 150px;
  padding: 10px;
  background-color: green;
  color: #fff;
  border: none;
  border-radius: 5px;
  margin-top: 50px;
  cursor: pointer;
  font-size: 16px;
}

.export-button:hover {
  background-color: darkgreen;
}

.welcome-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  margin-top: 50px;
  justify-content: center;
}

.logo {
  width: 150px; /* 调整为适合的宽度 */
  height: 150px; /* 保持图片纵横比 */
  margin-bottom: 30px; /* logo 与文字之间的间距 */
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
