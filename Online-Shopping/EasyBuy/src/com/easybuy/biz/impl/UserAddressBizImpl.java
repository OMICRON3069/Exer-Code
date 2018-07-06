package com.easybuy.biz.impl;

import com.easybuy.biz.UserAddressBiz;
import com.easybuy.dao.UserAddressDao;
import com.easybuy.dao.impl.UserAddressDaoImpl;
import com.easybuy.entity.UserAddress;
import com.easybuy.param.UserAddressParam;
import com.easybuy.util.DataSourceUtil;

import java.sql.Connection;
import java.util.List;

public class UserAddressBizImpl implements UserAddressBiz {
    @Override
    public List<UserAddress> queryUserAddressList(Integer id) {
        Connection connection = null;

        List<UserAddress> userAddressList = null;

        try {
            connection = DataSourceUtil.openConnection();
            UserAddressDao dao = new UserAddressDaoImpl(connection);
            UserAddressParam param = new UserAddressParam();
            param.setUserId(id);

            userAddressList = dao.queryUserAddressList(param);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return userAddressList;
    }

    @Override
    public Integer addUserAddress(Integer id, String address, String remark) {

        Connection connection = null;

        Integer cc = null;

        try {
            connection = DataSourceUtil.openConnection();
            UserAddressDao dao = new UserAddressDaoImpl(connection);
            UserAddress userAddress = new UserAddress();
            userAddress.setUserId(id);
            userAddress.setAddress(address);
            userAddress.setRemark(remark);

            cc = dao.add(userAddress);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc;
    }

    @Override
    public UserAddress getUserAddressById(Integer addressId) {
        Connection connection = null;

        UserAddress us = null;

        try {
            connection = DataSourceUtil.openConnection();
            UserAddressDao dao = new UserAddressDaoImpl(connection);


            us = dao.getUserAddressById(addressId);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return us;
    }
}
