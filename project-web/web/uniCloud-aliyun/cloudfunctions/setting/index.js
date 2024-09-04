'use strict';
const db = uniCloud.database();

exports.main = async (event, context) => {
  try {
    // 获取 user_info 表中的所有记录
    const collection = db.collection('user_info');

    // 为避免数据量大导致超时，分页读取数据
    let page = 0;
    const pageSize = 100; // 每次读取100条记录
    let hasMore = true;

    while (hasMore) {
      // 获取当前页的数据
      const result = await collection.skip(page * pageSize).limit(pageSize).get();
      const data = result.data;

      if (data.length === 0) {
        hasMore = false;
        break;
      }

      // 遍历当前页的数据并更新 orders 属性
      for (let record of data) {
        // 获取原始的 orders
        const orders = record.orders || [];

        // 过滤 orders 中的每个订单，仅保留指定的属性
        const newOrders = orders.map(order => {
          return {
            pay_mode: order.pay_mode,
            goods_num: order.goods_num,
            status_text: order.status_text,
            remark: order.remark,
            mobile: order.mobile,
            user_name: order.user_name,
            amount: order.amount,
            store: order.store,
            completed_time: order.completed_time,
            productioned_time: order.productioned_time,
            postscript: order.postscript,
            sort_num: order.sort_num,
            order_no: order.order_no,
            review: order.review,
            goods: order.goods
          };
        });

        // 更新数据库中的记录
        await collection.doc(record._id).update({
          orders: newOrders
        });
      }

      // 下一页
      page++;
    }

    return {
      success: true,
      message: '所有记录的 orders 属性已成功更新'
    };
  } catch (error) {
    console.error(error);
    return {
      success: false,
      message: error.message
    };
  }
};
