<template>
  <view>
    <!-- 搜索框和搜索按钮 -->
    <view class="search-container">
      <!-- 搜索框 -->
      <input 
        v-model="searchQuery" 
        placeholder="输入关键词搜索" 
        class="search-input" 
        @input="searchOrders" 
      />
      
      <!-- 搜索按钮 -->
      <uni-button 
        @click="searchOrders" 
        class="search-button" 
        type="primary" 
        size="mini"
      >
        搜索
      </uni-button>
	  
	  <!-- 导出按钮 -->
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
      :data="filteredOrders" 
      border 
      stripe 
      type="selection" 
      @selection-change="selectionChange"
    >
      <uni-tr>
        <uni-th align="center">订单编号</uni-th>
        <uni-th align="center">用户昵称</uni-th>
        <uni-th align="center">支付方式</uni-th>
        <uni-th align="center">金额</uni-th>
        <uni-th align="center">状态</uni-th>
        <uni-th align="center">时间</uni-th>
        <uni-th align="center">门店</uni-th>
        <uni-th align="center">操作</uni-th>
      </uni-tr>
      <uni-tr v-for="(order, index) in filteredOrders" :key="index">
        <uni-td align="center">{{ order.order_no }}</uni-td>
        <uni-td align="center">{{ order.user_name }}</uni-td>
        <uni-td align="center">{{ order.pay_mode }}</uni-td>
        <uni-td align="center">{{ order.amount }}</uni-td>
        <uni-td align="center">{{ order.status_text }}</uni-td>
        <uni-td align="center">{{ order.completed_time }}</uni-td>
        <uni-td align="center">{{ order.store_names }}</uni-td>
        <uni-td align="center">
          <uni-button @click="showDetails(order)" type="primary" size="mini">详情</uni-button>
        </uni-td>
      </uni-tr>
    </uni-table>

    <!-- 订单详情弹窗 -->
    <uni-popup class="orderDet-popup" ref="orderPopup" type="dialog" title="订单详情" mode="center">
      <view class="details-container">
        <view class="detail-item"><text class="label">订单编号:</text> <text class="value">{{ currentOrder.order_no }}</text></view>
        <view class="detail-item"><text class="label">用户昵称:</text> <text class="value">{{ currentOrder.user_name }}</text></view>
        <view class="detail-item"><text class="label">支付方式:</text> <text class="value">{{ currentOrder.pay_mode }}</text></view>
        <view class="detail-item"><text class="label">金额:</text> <text class="value">{{ currentOrder.amount }}</text></view>
		<view class="detail-item"><text class="label">就餐方式:</text> <text class="value">{{ currentOrder.postscript }}</text></view>
        <view class="detail-item"><text class="label">状态:</text> <text class="value">{{ currentOrder.status_text }}</text></view>
        <view class="detail-item"><text class="label">完成时间:</text> <text class="value">{{ currentOrder.completed_time }}</text></view>
        <view class="detail-item"><text class="label">门店:</text> <text class="value">{{ currentOrder.store_names }}</text></view>
        <view class="detail-item">
          <view class="goods-info-container">
            <text class="label">商品信息:</text>
            <view class="goods-list">
              <view v-for="(item, index) in currentOrder.goods" :key="index" class="goods-item">
                <view><text class="goods-label">商品名称:</text> <text class="goods-value">{{ item.name }}</text></view>
                <view><text class="goods-label">数量:</text> <text class="goods-value">{{ item.number }}</text></view>
                <view><text class="goods-label">价格:</text> <text class="goods-value">{{ item.price }}</text></view>
                <view><text class="goods-label">金额:</text> <text class="goods-value">{{ item.amount }}</text></view>
              </view>
            </view>
          </view>
        </view>
        <view class="detail-item"><text class="label">备注:</text> <text class="value">{{ currentOrder.remark ? currentOrder.remark : '【无备注！】'}}</text></view>
        <view class="detail-item"><text class="label">手机号码:</text> <text class="value">{{ currentOrder.mobile }}</text></view>
        <view class="detail-item"><text class="label">评论:</text> <text class="value">{{ currentOrder.review ? currentOrder.review : '【用户暂未进行评论！】'}}</text></view>
      </view>
      <view class="button-group">
        <uni-button @click="closeDetails" type="default" size="mini">关闭</uni-button>
      </view>
    </uni-popup>
  </view>
</template>




<script>
import user from '../../../store/modules/user';
export default {
  data() {
    return {
      orders: [], // 存储从云数据库获取的订单数据
      currentOrder: {}, // 存储当前查看的订单详情
      selectedIndexs: [], // 存储选中的订单项
      searchQuery: '', // 存储搜索框的输入
      filteredOrders: [] // 存储过滤后的订单数据
    };
  },
  methods: {
    async fetchOrders() {
      try {
        const db = uniCloud.database();
        const userInfoRes = await db.collection('user_info').get();
        const users = userInfoRes.result.data || [];
        this.orders = [];

        users.forEach(user => {
          if (user.orders && Array.isArray(user.orders)) {
            user.orders.forEach(order => {
              const orderData = {
                order_no: order.order_no,
                user_name: order.user_name,
                pay_mode: order.pay_mode,
                amount: order.amount,
                status_text: order.status_text,
                completed_time: order.completed_time,
                remark: order.remark,
                mobile: order.mobile,
                review: order.review,
                postscript: order.postscript,
                store_names: order.store.name,
                goods: Array.isArray(order.goods) ? order.goods : []
              };
              this.orders.push(orderData);
            });
          }
        });
        this.filteredOrders = this.orders; // 初次加载时设置为所有订单
      } catch (error) {
        console.error('获取订单数据失败：', error);
      }
    },
    searchOrders() {
      const query = (this.searchQuery || '').toLowerCase(); // 确保 searchQuery 是字符串
      if (typeof query !== 'string') {
        console.error('searchQuery should be a string');
        return;
      }
      this.filteredOrders = this.orders.filter(order => 
        (order.order_no || '').toLowerCase().includes(query) ||
        (order.user_name || '').toLowerCase().includes(query) ||
        (order.pay_mode || '').toLowerCase().includes(query) ||
        (order.completed_time || '').toLowerCase().includes(query) ||
        (order.status_text || '').toLowerCase().includes(query) ||
        (order.store_names || '').toLowerCase().includes(query) ||
        (order.mobile || '').toLowerCase().includes(query)
      );
    },
    showDetails(order) {
      this.currentOrder = order;
      this.$refs.orderPopup.open();
    },
    closeDetails() {
      this.$refs.orderPopup.close();
    },
    selectionChange(e) {
      this.selectedIndexs = e.detail.index;
    },
	exportExcel()
	{
		uni.navigateTo({
			url: '/pages/export/export'
		});
	}
  },
  mounted() {
    this.fetchOrders(); // 初次加载时获取订单数据
  }
};
</script>




<style scoped>
/* 其他样式 */

.search-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
}

/* 搜索框样式 */
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

/* 搜索按钮样式 */
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

.details-container {
  padding: 20px;
  max-height: 80vh; /* Adjust height as needed */
  overflow-y: auto; /* Enable vertical scroll */
  max-width: 90vw; /* Adjust width as needed */
  width: 100%;
  margin: 0 auto; /* Center the container */
  position: relative; /* Required for the custom scrollbar styling */
}

/* Hide scrollbar but keep scroll functionality */
.details-container::-webkit-scrollbar {
  width: 8px; /* Width of the scrollbar */
}

.details-container::-webkit-scrollbar-track```css
{
  background: transparent; /* Track background color */
}

.details-container::-webkit-scrollbar-thumb {
  background: rgba(0, 0, 0, 0.3); /* Scrollbar color */
  border-radius: 10px; /* Roundness of the scrollbar */
}

.details-container::-webkit-scrollbar-thumb:hover {
  background: rgba(0, 0, 0, 0.5);
}

.details-container::-webkit-scrollbar-button {
  display: none; /* Hide scrollbar arrows */
}

.detail-item {
  margin-bottom: 10px;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.label {
  font-weight: bold;
  text-align: left;
  width: 150px; /* Adjust width as needed */
}

.value {
  text-align: center;
  flex: 1;
}

.goods-info-container {
  margin-top: 10px;
}

.goods-list {
  margin-top: 10px;
  padding-left: 170px;
}

.goods-item {
  margin-bottom: 10px;
}

.goods-label {
  font-weight: bold;
}

.goods-value {
  margin-left: 10px;
}

.button-group {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
}
</style>



<style>
/* 确保自定义样式覆盖优先级 */
.orderDet-popup {
  background-color: white !important; /* 白色背景 */
  border-radius: 12px !important; /* 圆角 */
  padding: 20px !important; /* 内边距 */
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important; /* 阴影效果 */
}

/* 如果uni-popup组件内部包含内容容器，应用此样式 */
.orderDet-popup >>> .uni-popup__content {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
}

/* 强制覆盖弹窗的背景样式 */
.orderDet-popup >>> .uni-popup__wrapper {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important;
}


</style>