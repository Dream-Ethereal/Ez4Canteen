// 云函数：validateUser
'use strict';

exports.main = async (event, context) => {
  const db = uniCloud.database();
  const userCollection = db.collection('user_info');

  const { phone, password } = event;

  try {
    const res = await userCollection
      .where({ mobilePhone: phone, password: password })
      .get();

    // Check if any records are returned
    if (res.data.length > 0) {
      return { success: true, user: res.data[0] };
    } else {
      return { success: false, message: '用户不存在或密码错误' };
    }
  } catch (error) {
    console.error('数据库查询失败', error);
    return { success: false, error };
  }
};
