package com.easybuy.dao.impl;

import com.easybuy.dao.UserAddressDao;
import com.easybuy.entity.UserAddress;
import com.easybuy.param.UserAddressParam;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;

import java.sql.Connection;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class UserAddressDaoImpl extends BaseDaoImpl implements UserAddressDao {
    public UserAddressDaoImpl(Connection connection) {
        super(connection);
    }


    /**
     *
     * @param param Dynamic param
     */
    @Override
    public List<UserAddress> queryUserAddressList(UserAddressParam param) {

        ResultSet rs = null;

        List<UserAddress> userAddressList = new ArrayList<UserAddress>();

        StringBuffer sql = new StringBuffer(" select id, userId, address, createTime, " +
                "isDefault, remark from easybuy_address_user where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(param.getUserId())) {
            sql.append(" and userId = ? ");
            paramList.add("%"+param.getUserId()+"%");
        }

        if (EmptyUtils.isNotEmpty(param.getAddress())) {
            sql.append(" and address like ? ");
            paramList.add("%" + param.getAddress() + "%");
        }

        if (EmptyUtils.isNotEmpty(param.getSort())) {
            sql.append(" order by  " + param.getSort()+ "  ");
        }

        if (param.isPage()) {
            sql.append(" limit  "+ param.getStartIndex()+ " , " + param.getPageSize()+"  ");
        }


        rs = this.executeQuery(sql.toString(), paramList.toArray());

        try {
            while (rs.next()) {
                UserAddress userAddress = this.table2Class(rs);

                userAddressList.add(userAddress);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(rs);
        }
        return userAddressList;
    }

    @Override
    public Integer add(UserAddress userAddress) {

        Integer count = 0;

        String sql = " insert into easybuy_address_user " +
                "(userId, address, createTime, isDefault, remark) values(?,?,?,?,?) ";

        try {
            Object[] params = { userAddress.getUserId(), userAddress.getAddress(),
                    new Date(), 0, userAddress.getRemark()};

            count = this.executeInsert(sql, params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return count;
    }

    @Override
    public UserAddress getUserAddressById(Integer addressId) {
        return null;
    }

    @Override
    public UserAddress table2Class(ResultSet rs) throws Exception {
        UserAddress userAddress = new UserAddress();

        userAddress.setId(rs.getInt("id"));
        userAddress.setUserId(rs.getInt("userId"));
        userAddress.setCreateTime(rs.getDate("createTime"));
        userAddress.setRemark(rs.getString("remark"));
        userAddress.setAddress(rs.getString("address"));

        return userAddress;
    }


    public static void main(String[] args) {
        UserAddressDaoImpl daoImpl = new UserAddressDaoImpl(DataSourceUtil.openConnection());

        List<UserAddress> list = daoImpl.queryUserAddressList(new UserAddressParam());

        for (UserAddress userAddress: list) {
            System.out.println(userAddress.getUserId()+ " "+ userAddress.getAddress());
        }

    }
}
