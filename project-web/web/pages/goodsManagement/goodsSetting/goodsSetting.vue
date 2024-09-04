<template>
  <view class="container">
    <!-- 顶部工具栏 -->
    <view class="toolbar">
      <!-- 搜索框 -->
      <input
        v-model="searchKeyword"
        placeholder="搜索商品"
        class="search-input"
      />
      
      <!-- 搜索按钮 -->
      <uni-button @click="onSearch" class="search-button" type="primary" size="mini">搜索</uni-button>
      
      <!-- 新增商品按钮 -->
      <uni-button @click="openEditModal()" class="add-button" type="primary" size="mini">新增商品</uni-button>
    </view>

    <!-- 商品大类展示 -->
    <view v-for="(category, index) in filteredShopList" :key="index" class="category-container">
      <!-- 大类名称 -->
      <view class="category-name">{{ category.name }}</view>

      <!-- 商品列表，使用flex布局实现网格展示 -->
      <view class="grid-container">
        <view v-for="(goods, idx) in category.goods_list" :key="idx" class="grid-item">
          <image :src="goods.images" class="goods-image" />
          <view class="goods-content">{{ goods.name }}</view>
          <view class="goods-price">价格: {{ goods.price }}</view>
          <view class="goods-content">已售： {{ goods.sales }}</view>
          <!-- 底部按钮容器，使用flex布局实现左右布局 -->
          <view class="buttons-container">
            <!-- 上架/下架按钮 -->
            <uni-button
              @click="toggleSellStatus(category._id, idx, !goods.is_sell)"
              :class="{'sell-button': goods.is_sell, 'unsell-button': !goods.is_sell}"
            >
              {{ goods.is_sell ? '下架' : '上架' }}
            </uni-button>

            <!-- 编辑按钮 -->
            <uni-button @click="openEditModal(category._id, goods)" type="primary" class="edit-button">编辑</uni-button>
          </view>
        </view>
      </view>
    </view>

    <!-- 编辑弹窗 -->
    <uni-popup ref="editPopup" class="custom-popup" type="dialog" title="编辑商品" mode="center">
      <view class="form-container">
        <uni-forms ref="editForm" :model="editForm" :rules="rules">
          <!-- 大类选择框，仅在新增商品时显示 -->
          <uni-forms-item v-if="!editForm.id" label="选择大类" name="categoryId">
            <picker mode="selector" :range="shopList" range-key="name" v-model="editForm.categoryId" @change="onCategoryChange">
              <view :class="['picker', {'picker-selected': editForm.categoryId}]">
                {{ editForm.categoryId ? getCategoryName(editForm.categoryId) : '请选择大类' }}
              </view>
            </picker>
          </uni-forms-item>

          <uni-forms-item label="商品名称" name="name">
            <uni-easyinput v-model="editForm.name" placeholder="请输入商品名称" />
          </uni-forms-item>
          <uni-forms-item label="图片URL" name="image">
            <uni-easyinput v-model="editForm.images" placeholder="请输入图片URL" />
          </uni-forms-item>
          <uni-forms-item label="描述" name="content">
            <uni-easyinput v-model="editForm.content" placeholder="请输入描述" />
          </uni-forms-item>
          <uni-forms-item label="价格" name="price">
            <uni-easyinput v-model="editForm.price" placeholder="请输入价格" />
          </uni-forms-item>
        </uni-forms>
        <view class="button-group">
          
		  <view v-if="isEdit">
		  	<uni-button class="del_btn" @click="confirmDel">删除</uni-button>
		  </view>
		  <uni-button @click="confirmEdit" size="mini">确定</uni-button>
          <uni-button @click="cancelEdit" size="mini">取消</uni-button>
        </view>
      </view>
    </uni-popup>
  </view>
</template>

<script>
export default {
  data() {
    return {
      searchKeyword: '', // 搜索关键词
      shopList: [], // 大类和商品列表
      editForm: {
        categoryId: '',
        id: '', // 商品ID
        name: '',
        images: '',
        content: '',
        price: 0
      },
      rules: {
        name: { required: true, message: '请输入商品名称' },
        images: { required: true, message: '请输入图片URL' },
        content: { required: true, message: '请输入描述' },
        price: { required: true, message: '请输入价格' }
      },
	  isEdit : false
    };
  },
  computed: {
    filteredShopList() {
      if (!this.searchKeyword) {
        return this.shopList;
      }
      const keyword = this.searchKeyword.toLowerCase();
      return this.shopList.map(category => {
        const filteredGoods = category.goods_list.filter(goods =>
          goods.name.toLowerCase().includes(keyword)
        );
        return { ...category, goods_list: filteredGoods };
      }).filter(category => category.goods_list.length > 0);
    }
  },
  methods: {
    onSearch() {
      // 触发过滤逻辑
    },
    openEditModal(categoryId, goods = {}) {
      if (!categoryId) {
        // 如果categoryId为空，表示新增商品，重置表单
        this.editForm = {
          categoryId: '',
          id: '', // 新商品无_id
          name: '',
          images: '',
          content: '',
          price: 0
        };
		this.isEdit = false;
      } else {
        // 编辑商品
		this.isEdit = true;
        this.editForm = { ...goods, categoryId };
      }
      this.$refs.editPopup.open(); // 显示弹窗
    },
    cancelEdit() {
      this.$refs.editPopup.close(); // 关闭弹窗
    },
    async confirmEdit() {
      try {
        const db = uniCloud.database();
    
        // 如果是新增商品
        if (!this.editForm.id) {
          // 获取对应的大类
          const res = await db.collection('shop_list').where({_id: this.editForm.categoryId}).get();
          if (res.result.data.length === 0) {
            console.error("未找到对应的大类记录");
            return;
          }
          const categoryDoc = res.result.data[0];
		  
          const now = new Date();
          const time = Math.floor(now.getTime() / 1000) 
          const goodid = `GS${time}`
          // 新增商品，推入 goods_list
          categoryDoc.goods_list.push({
            id: goodid, // 为新商品生成唯一ID
            name: this.editForm.name,
            content: this.editForm.content,
            price: this.editForm.price,
            images: this.editForm.images,
            is_sell: false, // 默认未上架
			sales: 0
          });
		  
		  
    
          // 更新数据库中的记录
          await db.collection('shop_list').doc(this.editForm.categoryId).update({
            goods_list: categoryDoc.goods_list
          });
        } else {
          // 编辑商品的逻辑保持不变
          const res = await db.collection('shop_list').where({_id: this.editForm.categoryId}).get();
          if (res.result.data.length === 0) {
            console.error("未找到对应的大类记录");
            return;
          }
          const categoryDoc = res.result.data[0];
          const goodsIndex = categoryDoc.goods_list.findIndex(goods => goods.id === this.editForm.id);
          if (goodsIndex === -1) {
            console.error("未找到对应的商品记录");
            return;
          }
    
          // 更新商品信息
          categoryDoc.goods_list[goodsIndex].name = this.editForm.name;
          categoryDoc.goods_list[goodsIndex].content = this.editForm.content;
          categoryDoc.goods_list[goodsIndex].price = this.editForm.price;
          categoryDoc.goods_list[goodsIndex].images = this.editForm.images;
    
          // 更新数据库中的记录
          await db.collection('shop_list').doc(this.editForm.categoryId).update({
            goods_list: categoryDoc.goods_list
          });
        }
    
        this.$refs.editPopup.close(); // 关闭弹窗
        this.fetchShopList(); // 重新获取商品列表
      } catch (error) {
        console.error("更新商品时发生错误：", error);
      }
    },
    async toggleSellStatus(categoryId, goodsIndex, isSell) {
      try {
        const db = uniCloud.database();
        const res = await db.collection('shop_list').where({_id: categoryId}).get();
        if (res.result.data.length === 0) {
          console.error("未找到对应的大类文档");
          return;
        }
        const categoryDoc = res.result.data[0];
        categoryDoc.goods_list[goodsIndex].is_sell = isSell;
        await db.collection('shop_list').doc(categoryDoc._id).update({
          goods_list: categoryDoc.goods_list
        });
        location.reload();
      } catch (error) {
        console.error("更新商品销售状态时发生错误：", error);
      }
    },
    async fetchShopList() {
      try {
        const db = uniCloud.database();
        const res = await db.collection('shop_list').get();
        if (res.result.data.length > 0) {
          this.shopList = res.result.data;
        } else {
          this.shopList = [];
        }
      } catch (error) {
        console.error("查询数据库时发生错误：", error);
      }
    },
    // 获取大类名称
    getCategoryName(categoryId) {
      const category = this.shopList.find(item => item._id === categoryId);
      return category ? category.name : '';
    },
    
    // 大类选择框的change事件
    onCategoryChange(event) {
      this.editForm.categoryId = this.shopList[event.detail.value]._id;
    },
	async confirmDel() {
	  try {
	    const res = await uni.showModal({
	      title: '确认删除',
	      content: '您确定要删除此商品吗？',
	      confirmText: '删除',
	      cancelText: '取消'
	    });
	
	
	    if (!res.confirm) {
	      // 如果用户确认删除
	      const db = uniCloud.database();
	      const res = await db.collection('shop_list').where({_id: this.editForm.categoryId}).get();
	      if (res.result.data.length === 0) {
	        console.error("未找到对应的大类记录");
	        return;
	      }
	      const categoryDoc = res.result.data[0];
	      const goodsIndex = categoryDoc.goods_list.findIndex(goods => goods.id === this.editForm.id);
	      if (goodsIndex === -1) {
	        console.error("未找到对应的商品记录");
	        return;
	      }
	
	      // 从商品列表中移除商品
	      categoryDoc.goods_list.splice(goodsIndex, 1);
	
	      // 更新数据库中的记录
	      await db.collection('shop_list').doc(this.editForm.categoryId).update({
	        goods_list: categoryDoc.goods_list
	      });
	
	      console.log("商品已删除");  // 调试信息
	
	      // 关闭弹窗
	      this.$refs.editPopup.close();
	      this.fetchShopList(); // 重新获取商品列表
	    }
	  } catch (error) {
	    console.error("删除商品时发生错误：", error);
	  }
	}
  },
  mounted() {
    this.fetchShopList();
  }
}
</script>




<style scoped>
/* 容器样式 */
.container {
  padding: 10px;
}

/* 顶部工具栏样式 */
.toolbar {
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
  font-size: 12px;
}

/* 搜索按钮样式 */
.search-button {
  margin-right: 10px;
}

/* 新增商品按钮样式 */
.add-button {
  flex-shrink: 0;
}

/* 大类名称样式 */
.category-container {
  margin-bottom: 20px;
}

.category-name {
  font-size: 18px;
  font-weight: bold;
  margin-bottom: 10px;
}

/* 网格容器样式 */
.grid-container {
  display: flex;
  flex-wrap: wrap;
  gap: 10px;
}

/* 每个格子的样式 */
.grid-item {
  width: calc(25% - 10px); /* 每行四个商品 */
  box-sizing: border-box;
  border: 1px solid #ddd;
  border-radius: 8px;
  padding: 10px;
  background-color: #fff;
  text-align: center;
}

/* 商品图像样式 */
.goods-image {
  width: 100%;
  height: 120px;
  object-fit: cover;
  border-radius: 8px;
}

/* 商品内容样式 */
.goods-content {
  margin: 10px 0;
  font-size: 14px;
}

/* 商品价格样式 */
.goods-price {
  margin-bottom: 10px;
  font-size: 16px;
  color: #f40;
}

/* 底部按钮容器样式 */
.buttons-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 10px;
}

/* 上架按钮样式 */
.sell-button {
  background-color: red;
  color: white;
}

/* 下架按钮样式 */
.unsell-button {
  background-color: blue;
  color: white;
}

.del_btn {
  background-color: red;
  color: white;
}

/* 编辑按钮样式 */
.edit-button {
  flex-shrink: 0;
}

/* 表单容器样式 */
.form-container {
  padding: 20px;
}

/* 按钮组样式 */
.button-group {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
}


</style>

<style>
/* 确保自定义样式覆盖优先级 */
.custom-popup {
  background-color: white !important; /* 白色背景 */
  border-radius: 12px !important; /* 圆角 */
  padding: 20px !important; /* 内边距 */
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important; /* 阴影效果 */
}

/* 如果uni-popup组件内部包含内容容器，应用此样式 */
.custom-popup >>> .uni-popup__content {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
}

/* 强制覆盖弹窗的背景样式 */
.custom-popup >>> .uni-popup__wrapper {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important;
}

/* 大类选择框样式 */
.picker {
  padding: 10px;
  background-color: #f5f5f5;
  border: 1px solid #ddd;
  border-radius: 4px;
  text-align: left;
  font-size: 14px;
  color: #aaa;
}

.picker-selected {
  color: #333; /* 选中后的字体颜色 */
}

.picker-container {
  margin-bottom: 20px;
}

</style>
