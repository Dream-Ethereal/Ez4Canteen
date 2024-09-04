'use strict';

exports.main = async (event, context) => {
  const db = uniCloud.database();
  const userCollection = db.collection('user_info');

  const { mobilePhone, nickname, gender, birthday } = event;

  try {
    // 确保 mobilePhone 存在于参数中
    if (!mobilePhone) {
      throw new Error('缺少 mobilePhone');
    }

    // 更新用户信息
    const updateData = {};
    if (nickname) updateData.nickname = nickname;
    if (gender) updateData.gender = gender;
    if (birthday) updateData.birthday = birthday;

    const res = await userCollection.where({ mobilePhone }).update(updateData);
    
    if (res.updated > 0) {
      return { success: true, data: res };
    } else {
      return { success: false, message: '未找到用户或更新失败' };
    }
  } catch (error) {
    console.error('更新数据库失败', error);
    return { success: false, error: error.message };
  }
};
