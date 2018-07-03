package com.easybuy.dao.impl;

import com.easybuy.dao.OrderDao;
import com.easybuy.entity.Order;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class OrderDaoImpl extends BaseDaoImpl implements OrderDao {
    public OrderDaoImpl(Connection connection) {
        super(connection);
    }

    public static void main(String[] args) {
        OrderDaoImpl jibai = new OrderDaoImpl(DataSourceUtil.openConnection());

        Order eleme = new Order();

        eleme.setUserId(2);
        eleme.setLoginName("Dick");
        eleme.setUserAddress("钓鱼岛");
        eleme.setCost((float) 8848);
        eleme.setSerialNumber("666999967897897979766");

        eleme = jibai.getOrderById(1);

        //System.out.println(eleme.getSerialNumber());
        //System.out.println(jibai.count(null));

        List<Order> Vegetable = jibai.getOrderList(1,1,1000);
        for (Order hot:Vegetable) {
            System.out.println(hot.getSerialNumber() + "  " + hot.getLoginName());
        }

    }

    @Override
    public void add(Order order) {
        String sql = " insert into easybuy_order (userId, loginName, userAddress, " +
                " createTime, cost, serialNumber) values( ?,?,?,?,?,? ) ";

        Object[] params = { order.getUserId(), order.getLoginName(), order.getUserAddress(),
                new Date(), order.getCost(), order.getSerialNumber() };

        this.executeInsert(sql,params);
    }

    @Override
    public void deleteById(Integer id) {
        String sql = " delete from easybuy_order where id = ? ";

        Object[] params = { id };

        this.executeUpdate(sql,params);
    }

    @Override
    public Order getOrderById(Integer id) {
        String sql = " select * from easybuy_order where id = ? ";

        Object[] params = { id };

        Order jibai = new Order();

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql,params);

            while (resultSet.next()) {
                jibai = table2Class(resultSet);

            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }
        return jibai;
    }

    @Override
    public Integer count(Integer userId) {
        StringBuffer sql = new StringBuffer( " select * from easybuy_order where 1=1  ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(userId)) {
            sql.append(" and userId = ? ");
            paramList.add(userId);
        }

        Integer count = 0;
        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql.toString(), paramList.toArray());

            while (resultSet.next()) {
                count = resultSet.getRow();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }
        return count;
    }

    @Override
    public List<Order> getOrderList(Integer userId, Integer currentPageNo, Integer pageSize) {

        List<Order> orderList = new ArrayList<Order>();

        StringBuffer sql = new StringBuffer(" select * from easybuy_order where 1=1 ");

        List<Object> paramsList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(userId)) {
            sql.append(" and userId = ? ");
            paramsList.add(userId);
        }

        ResultSet resultSet = null;



        try {
            int total = count(null);

            Pager page = new Pager(total, pageSize, currentPageNo);

            sql.append(" limit  "+ (page.getCurrentPage() -1)*page.getRowPerpage() +
                    " , " + page.getRowPerpage());

            resultSet = this.executeQuery(sql.toString(),paramsList.toArray());

            while (resultSet.next()) {
                Order order = table2Class(resultSet);
                orderList.add(order);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return orderList;
    }

    @Override
    public Order table2Class(ResultSet rs) throws Exception {
        Order niggaOrder = new Order();

        niggaOrder.setId(rs.getInt("id"));
        niggaOrder.setUserId(rs.getInt("userId"));
        niggaOrder.setLoginName(rs.getString("loginName"));
        niggaOrder.setUserAddress(rs.getString("userAddress"));
        niggaOrder.setCreateTime(rs.getDate("createTime"));
        niggaOrder.setCost(rs.getFloat("cost"));
        niggaOrder.setSerialNumber(rs.getString("serialNumber"));

        return niggaOrder;
    }
}
