package com.easybuy.dao.impl;

import com.easybuy.dao.OrderDetailDao;
import com.easybuy.entity.OrderDetail;
import com.easybuy.entity.Product;
import com.easybuy.param.OrderDetailParam;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class OrderDetailDaoImpl extends BaseDaoImpl implements OrderDetailDao {
    public OrderDetailDaoImpl(Connection connection) {
        super(connection);
    }

    public static void main(String[] args) {
        OrderDetailDao jibai = new OrderDetailDaoImpl(DataSourceUtil.openConnection());

        OrderDetail oo = new OrderDetail();

        Product pp = new Product();
        pp.setId(888);
        oo.setOrderId(4);
        oo.setProduct(pp);
        oo.setQuantity(88888);
        oo.setCost((float) 8848);
        oo.setId(3);
        //jibai.deleteById(oo);
        //System.out.println(jibai.count());
        //System.out.println(jibai.getOrderDetailById(1).getCost());
        List<OrderDetail> pop = jibai.getOrderDetail(null);
        for (OrderDetail pipi: pop) {
            System.out.println(pipi.getCost());
        }
    }

    @Override
    public void add(OrderDetail detail) {
        String sql = " insert into easybuy_order_detail (orderId, " +
                " productId, quantity, cost) values(?,?,?,?) ";

        Object[] params= { detail.getOrderId(), detail.getProduct().getId(),
                detail.getQuantity(), detail.getCost() };

        this.executeInsert(sql,params);
    }

    @Override
    public void deleteById(OrderDetail detail) {
        String sql = " delete from easybuy_order_detail where id = ? ";
        Object[] params = { detail.getId() };
        this.executeUpdate(sql,params);

    }

    @Override
    public Integer count() {
        Integer ccc = 0;

        String sql = " select * from easybuy_order_detail ";

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql,null);

            while (resultSet.next()) {
                ccc = resultSet.getRow();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return ccc;
    }

    @Override
    public OrderDetail getOrderDetailById(Integer id) {
        OrderDetail ob = new OrderDetail();

        String sql = " select * from easybuy_order_detail where id = ?  ";

        Object[] params = { id };

        ResultSet resultSet = null;


        try {
            resultSet = this.executeQuery(sql, params);

            while (resultSet.next()) {
                ob = table2Class(resultSet);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return ob;
    }

    @Override
    public List<OrderDetail> getOrderDetail(Integer orderId) {

        List<OrderDetail> orderDetailList = new ArrayList<OrderDetail>();

        StringBuffer sql = new StringBuffer(" select * from easybuy_order_detail where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(orderId)) {
            sql.append(" and orderId = ? ");
            paramList.add(orderId);
        }

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql.toString(),paramList.toArray());

            while (resultSet.next()) {
                OrderDetail orderDetail = this.table2Class(resultSet);
                orderDetailList.add(orderDetail);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return orderDetailList;
    }

    @Override
    public OrderDetail table2Class(ResultSet rs) throws Exception {
        OrderDetail nigga = new OrderDetail();

        nigga.setId(rs.getInt("id"));
        nigga.setCost(rs.getFloat("cost"));
        nigga.setOrderId(rs.getInt("orderId"));
        nigga.setQuantity(rs.getInt("quantity"));
        nigga.setProductId(rs.getInt("productId"));

        return nigga;
    }
}
