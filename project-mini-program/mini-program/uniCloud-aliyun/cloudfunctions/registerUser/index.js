'use strict';

exports.main = async (event, context) => {
  const db = uniCloud.database();
  const userCollection = db.collection('user_info');

  const { newUser } = event;

  try {
    // 插入新用户数据
    const res = await userCollection.add(newUser);
    return { success: true, id: res._id };
  } catch (error) {
    console.error('插入用户失败', error);
    return { success: false, error };
  }
};
