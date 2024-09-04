<template>
  <view class="container">
    <!-- 顶部工具栏 -->
    <view class="toolbar">
      <!-- 新增大类按钮 -->
	  <button class="add-button" type="primary" size="mini" @click="openAddModal">新增大类</button>
    </view>

    <!-- 大类列表 -->
    <uni-table ref="categoryTable" :data="shopList" border stripe type="selection" @selection-change="selectionChange">
      <uni-tr>
        <uni-th align="center">ID</uni-th>
        <uni-th align="center">名称</uni-th>
        <uni-th align="center">操作</uni-th>
      </uni-tr>
      <uni-tr v-for="(category, index) in shopList" :key="index">
        <uni-td align="center">{{ category._id }}</uni-td>
        <uni-td align="center">{{ category.name }}</uni-td>
        <uni-td align="center">
          <view class="actions">
            <uni-button @click="openEditModal(category)" type="primary" class="action-button" size="mini">编辑</uni-button>
            <uni-button @click="confirmDelete(category._id)" type="warn" class="action-button" size="mini">删除</uni-button>
          </view>
        </uni-td>
      </uni-tr>
    </uni-table>

    <!-- 新增/编辑弹窗 -->
    <uni-popup class="category-popup" ref="categoryPopup" type="dialog" title="编辑大类" mode="center">
      <view class="form-container">
        <uni-forms ref="categoryForm" :model="form" :rules="rules">
          <uni-forms-item label="Icon路径" name="icon">
            <uni-easyinput v-model="form.icon" placeholder="请输入Icon路径" />
          </uni-forms-item>
          <uni-forms-item label="名称" name="name">
            <uni-easyinput v-model="form.name" placeholder="请输入大类名称" />
          </uni-forms-item>
        </uni-forms>
        <view class="button-group">
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
      shopList: [], // 大类列表
      form: {
        _id: '',
        icon: '',
        name: ''
      },
      rules: {
        icon: { required: true, message: '请输入Icon路径' },
        name: { required: true, message: '请输入大类名称' }
      },
      isEdit: false, // 用于区分新增和编辑
      selectedIndexs: [] // 用于处理选中的项
    };
  },
  methods: {
    async fetchShopList() {
      try {
        const db = uniCloud.database();
        const res = await db.collection('shop_list').get();
        this.shopList = res.result.data || [];
      } catch (error) {
        console.error('获取大类列表失败：', error);
      }
    },
    openAddModal() {
      this.isEdit = false;
      this.form = { _id: '', icon: '', name: '' };
      this.$refs.categoryPopup.open();
    },
    openEditModal(category) {
      this.isEdit = true;
      this.form = { ...category };
      this.$refs.categoryPopup.open();
    },
    async confirmSave() {
      try {
        const db = uniCloud.database();
    
        if (this.isEdit) {
          // 编辑大类
          await db.collection('shop_list').doc(this.form._id).update({
            icon: this.form.icon,
            name: this.form.name
          });
        } else {
          // 新增大类
          const maxIdRes = await db.collection('shop_list').aggregate().group({
            _id: null,
            maxId: db.command.aggregate.max('$id')
          }).end();
          
		  const _id = await this.generateId(); // 生成_id
		  
          const maxId = maxIdRes.list && maxIdRes.list.length > 0 ? maxIdRes.list[0]?.maxId : 0; // 确保有值或设置为0
          const newId = maxId + 1; // 生成新的id
    
          await db.collection('shop_list').add({
            _id: _id, // 保持原有_id
            icon: this.form.icon,
            name: this.form.name,
            goods_list: [], // 初始化为空商品列表
            id: newId // 添加新的id属性
          });
        }
    
        this.$refs.categoryPopup.close();
        this.fetchShopList(); // 刷新列表
      } catch (error) {
        console.error('保存大类失败：', error);
      }
    },
    cancelSave() {
      this.$refs.categoryPopup.close();
    },
    async confirmDelete(categoryId) {
      const res = await uni.showModal({
        title: '确认删除',
        content: '您确定要删除此大类及其所有商品吗？',
        confirmText: '删除',
        cancelText: '取消',
		success:function(res){
			if (res.confirm) {
			    const db = uniCloud.database();
			    db.collection('shop_list').where({_id:categoryId}).remove(); // 删除大类
			    location.reload();
			}
		}
      });

      
    },
    async generateId() {
      const db = uniCloud.database();
	  const now = new Date();
	  const time = Math.floor(now.getTime() / 1000) 
      const newId = `CT${time}`;
      const existingDoc = await db.collection('shop_list').doc(newId).get();
      if (existingDoc.result.data.length > 0) {
        return this.generateId(); // 如果_id冲突，重新生成
      }
      return newId;
    },
    selectionChange(e) {
      this.selectedIndexs = e.detail.index;
    }
  },
  mounted() {
    this.fetchShopList(); // 初次加载时获取大类列表
  }
};
</script>

<style scoped>
.container {
  padding: 10px;
}

/* 按钮样式 */
.toolbar {
  display: flex;
  justify-content: flex-end; 
  align-items: center;
  margin-bottom: 20px;
  width: 100%;  
}

.add-button {
  padding: 5px 10px; 
  font-size: 14px;
  margin: 0;
  width: auto; 
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

.actions {
  display: flex;
  justify-content: center;
  gap: 3px; /* 缩小到3px */
}

.action-button {
  padding: 5px 8px; /* 缩小按钮 */
  font-size: 12px;
  margin: 0; /* 确保没有额外的外边距 */
}


.form-container {
  padding: 20px;
}

.button-group {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
}

.form-button {
  padding: 5px 10px;
  font-size: 14px;
  margin: 0;
}
</style>


<style>
/* 确保自定义样式覆盖优先级 */
.category-popup {
  background-color: white !important; /* 白色背景 */
  border-radius: 12px !important; /* 圆角 */
  padding: 20px !important; /* 内边距 */
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important; /* 阴影效果 */
}

/* 如果uni-popup组件内部包含内容容器，应用此样式 */
.category-popup >>> .uni-popup__content {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
}

/* 强制覆盖弹窗的背景样式 */
.category-popup >>> .uni-popup__wrapper {
  background-color: white !important;
  border-radius: 12px !important;
  padding: 20px !important;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1) !important;
}


</style>
