'use strict';

const db = uniCloud.database();

exports.main = async (event, context) => {
  try {
    // 查询商品数据
    const goodsCollection = db.collection('shop_list');
    const goodsResult = await goodsCollection.get();

    // 返回商品数据
    return {
      code: 200,
      data: goodsResult.data,
    };
  } catch (error) {
    // 捕获任何错误，并返回错误信息
    return {
      code: 500,
      message: 'An error occurred while fetching goods data',
      error: error.message,
    };
  }
};
