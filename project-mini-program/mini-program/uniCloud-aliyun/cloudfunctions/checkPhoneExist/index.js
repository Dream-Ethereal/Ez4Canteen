'use strict';

exports.main = async (event, context) => {
  const db = uniCloud.database();
  const userCollection = db.collection('user_info');

  const { phone } = event;

  try {
    const res = await userCollection.where({ mobilePhone: phone }).get();
    return { exists: res.data.length > 0 };
  } catch (error) {
    console.error('查询手机号失败', error);
    return { error };
  }
};
