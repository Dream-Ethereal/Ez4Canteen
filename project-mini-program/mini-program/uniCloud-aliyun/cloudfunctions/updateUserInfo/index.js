'use strict';

exports.main = async (event, context) => {
  const db = uniCloud.database();
  const userCollection = db.collection('user_info');

  const { mobilePhone, updateData } = event;

  try {
    // Update user information
    const res = await userCollection.where({ mobilePhone }).update(updateData);
    return { success: true, data: res };
  } catch (error) {
    console.error('更新数据库失败', error);
    return { success: false, error };
  }
};
