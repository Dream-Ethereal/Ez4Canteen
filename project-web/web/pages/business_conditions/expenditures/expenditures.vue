<template>
  <view>
    <!-- 搜索框和搜索按钮 -->
    <view class="search-container">
      <input 
        v-model="searchQuery" 
        placeholder="输入关键词搜索" 
        class="search-input" 
        @input="searchOrders" 
      />
      <uni-button 
        @click="searchOrders" 
        class="search-button" 
        type="primary" 
        size="mini"
      >
        搜索
      </uni-button>
      <uni-button
        @click="openAddExpenditurePopup" 
        class="search-button" 
        type="primary" 
        size="mini"
      >
        新增支出
      </uni-button>
	  
	  <uni-button
	    @click="exportExcel" 
	    class="search-button" 
	    type="primary" 
	    size="mini"
	  >
	    导出为Excel
	  </uni-button>
    </view>

    <!-- 订单表格 -->
    <uni-table 
      ref="orderTable" 
      :data="filteredExpenditures" 
      border 
      stripe 
      type="selection" 
      @selection-change="selectionChange"
    >
      <uni-tr>
        <uni-th align="center">编号</uni-th>
        <uni-th align="center">时间</uni-th>
        <uni-th align="center">支出金额</uni-th>
        <uni-th align="center">使用者</uni-th>
        <uni-th align="center">备注</uni-th>
        <uni-th align="center">操作</uni-th>
      </uni-tr>
      <uni-tr v-for="(expenditure, index) in filteredExpenditures" :key="index">
        <uni-td align="center">{{ expenditure.id }}</uni-td>
        <uni-td align="center">{{ expenditure.time }}</uni-td>
        <uni-td align="center">{{ expenditure.amount }}</uni-td>
        <uni-td align="center">{{ expenditure.implementer }}</uni-td>
        <uni-td align="center">{{ expenditure.remark }}</uni-td>
        <uni-td align="center">
          <uni-button @click="openEditExpenditurePopup(expenditure)" type="primary" size="mini">编辑</uni-button>
        </uni-td>
      </uni-tr>
    </uni-table>

    <!-- 新增/编辑支出弹窗 -->
    <uni-popup class="expenditure-popup" ref="expenditurePopup" type="dialog" title="编辑支出" mode="center">
      <view class="form-container">
        <uni-forms ref="expenditureForm" :model="currentExpenditure" :rules="rules">
          <uni-forms-item label="编号" name="id">
            <uni-easyinput v-model="currentExpenditure.id" placeholder="自动生成编号" disabled />
          </uni-forms-item>
          <uni-forms-item label="时间" name="time">
            <uni-datetime-picker 
              v-model="currentExpenditure.time" 
              type="datetime" 
              :return-type="'string'" 
              :start="startDate"
              :end="endDate"
              placeholder="请选择时间"
              format="yyyy-MM-dd HH:mm:ss"
            />
          </uni-forms-item>
          <uni-forms-item label="支出金额" name="amount">
            <uni-easyinput v-model="currentExpenditure.amount" placeholder="请输入支出金额" />
          </uni-forms-item>
          <uni-forms-item label="使用者" name="implementer">
            <uni-easyinput v-model="currentExpenditure.implementer" placeholder="请输入使用者" />
          </uni-forms-item>
          <uni-forms-item label="备注" name="remark">
            <uni-easyinput v-model="currentExpenditure.remark" placeholder="请输入备注" />
          </uni-forms-item>
        </uni-forms>
        <view class="button-group">
          <uni-button v-if="isEditMode" @click="confirmDelete" type="warn" class="form-button">删除</uni-button>
          <uni-button @click="confirmSave" type="primary" class="form-button">确认</uni-button>
          <uni-button @click="cancelSave" class="form-button">取消</uni-button>
        </view>
      </view>
    </uni-popup>
  </view>
</template>

<script>
export default {
  data() {
    return {
      expenditures: [],
      searchQuery: '',
      filteredExpenditures: [],
      currentExpenditure: {
        id: '',
        time: this.formatDateTime(new Date()), // 默认设置为当前时间
        amount: '',
        implementer: '',
        remark: ''
      },
      isEditMode: false,
      rules: {
        time: { required: true, message: '请输入时间' },
        amount: { required: true, message: '请输入支出金额' },
        implementer: { required: true, message: '请输入使用者' },
        remark: { required: true, message: '请输入备注' }
      },
      startDate: this.formatDateTime(new Date(new Date().setFullYear(new Date().getFullYear() - 1))), // 起始时间为一年前
      endDate: this.formatDateTime(new Date(new Date().setFullYear(new Date().getFullYear() + 1))) // 结束时间为一年后
    };
  },
  async mounted() {
      await this.getExpendituresData();
    },
  methods: {
    formatDateTime(date) {
      const year = date.getFullYear();
      const month = String(date.getMonth() + 1).padStart(2, '0');
      const day = String(date.getDate()).padStart(2, '0');
      const hours = String(date.getHours()).padStart(2, '0');
      const minutes = String(date.getMinutes()).padStart(2, '0');
      const seconds = String(date.getSeconds()).padStart(2, '0');
      return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    },
    async getExpendituresData() {
      try {
        const db = uniCloud.database();
        const res = await db.collection('expenditures').get();
        this.expenditures = res.result.data;
        this.filteredExpenditures = this.expenditures;
      } catch (error) {
        console.error('获取支出数据失败：', error);
      }
    },
    
    searchOrders() {
      const query = this.searchQuery.toLowerCase();
      this.filteredExpenditures = this.expenditures.filter(expenditure => 
        expenditure.id.toString().toLowerCase().includes(query) || 
        expenditure.time.toLowerCase().includes(query) || 
        expenditure.amount.toString().includes(query) ||
        expenditure.implementer.toLowerCase().includes(query) ||
        expenditure.remark.toLowerCase().includes(query)
      );

    },
    openAddExpenditurePopup() {
      this.isEditMode = false;
      this.currentExpenditure = {
        id: `OUT_${this.expenditures.length + 1}`,
        time: this.formatDateTime(new Date()), // 新建时默认设置为当前时间
        amount: '',
        implementer: '',
        remark: ''
      };
      this.$refs.expenditurePopup.open();
    },
    openEditExpenditurePopup(expenditure) {
      this.isEditMode = true;
      this.currentExpenditure = { ...expenditure };
      this.$refs.expenditurePopup.open();
    },
    async confirmSave() {
      const db = uniCloud.database();
      try {
        const updateData = { ...this.currentExpenditure };
        delete updateData._id; // 删除 _id 字段，以避免更新时修改它
    
        if (this.isEditMode) {
          await db.collection('expenditures').doc(this.currentExpenditure._id).update(updateData);
        } else {
          await db.collection('expenditures').add(this.currentExpenditure);
        }
        await this.getExpendituresData();
        this.$refs.expenditurePopup.close();
      } catch (error) {
        console.error('操作失败：', error);
      }
    },
    async confirmDelete() {
      uni.showModal({
        title: '确认删除',
        content: '确定要删除这条记录吗？',
        success: async (res) => {
          if (res.confirm) {
            try {
              const db = uniCloud.database();
              await db.collection('expenditures').doc(this.currentExpenditure._id).remove();
              await this.getExpendituresData();
              this.$refs.expenditurePopup.close();
            } catch (error) {
              console.error('删除失败：', error);
            }
          } else if (res.cancel) {
            console.log('用户取消了删除操作');
          }
        }
      });
    },
    cancelSave() {
      this.$refs.expenditurePopup.close();
    },
    selectionChange(selected) {
      // 处理选中项变化的逻辑
    },
	exportExcel()
	{
		uni.navigateTo({
			url: '/pages/export/export'
		});
	}
  }
};
</script>

<style scoped>
.container {
  padding: 20px;
  font-family: Arial, sans-serif;
}

.search-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
}

.search-input {
  flex: 1;
  padding: 8px;
  border: 1px solid #ddd;
  border-radius: 4px;
  margin-right: 10px;
  margin-top: 15px;
  margin-left: 10px;
  font-size: 12px;
}

.search-button {
  margin-top: 15px;
  margin-right: 10px;
}

.uni-table {
  width: 100%;
  border-collapse: collapse;
}

.uni-th, .uni-td {
  padding: 10px;
  text-align: center;
}

.uni-tr {
  border-bottom: 1px solid #ddd;
}

.uni-button {
  margin: 0 5px;
}

.expenditure-popup {
  width:80%;
}

.form-container {
  padding: 20px;
}

.uni-forms-item {
  margin-bottom: 15px;
}

.button-group {
  display: flex;
  justify-content: flex-end;
}

.form-button {
  margin-left: 10px;
}
</style>


<style>
/* 确保自定义样式覆盖优先级 */
.expenditure-popup {
  background-color: white !important; /* 白色背景 */
  border-radius: 12px !important; /* 圆角 */
  padding: 20px !important; /* 内边距 */
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important; /* 阴影效果 */
}

/* 如果uni-popup组件内部包含内容容器，应用此样式 */
.expenditure-popup >>> .uni-popup__content {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
}

/* 强制覆盖弹窗的背景样式 */
.expenditure-popup >>> .uni-popup__wrapper {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important;
}
</style>
