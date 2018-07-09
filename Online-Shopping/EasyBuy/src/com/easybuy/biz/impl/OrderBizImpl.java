package com.easybuy.biz.impl;

import com.easybuy.biz.OrderBiz;
import com.easybuy.dao.OrderDao;
import com.easybuy.dao.OrderDetailDao;
import com.easybuy.dao.ProductDao;
import com.easybuy.dao.impl.OrderDaoImpl;
import com.easybuy.dao.impl.OrderDetailDaoImpl;
import com.easybuy.dao.impl.ProductDaoImpl;
import com.easybuy.entity.Order;
import com.easybuy.entity.OrderDetail;
import com.easybuy.entity.User;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.ShoppingCart;
import com.easybuy.util.ShoppingCartItem;
import com.easybuy.util.StringUtils;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class OrderBizImpl implements OrderBiz {
    @Override
    public Order payShoppingCart(ShoppingCart cart, User user, String address) {
        Connection connection = null;

        Order order = new Order();
        connection = DataSourceUtil.openConnection();

        try {
            connection.setAutoCommit(false);
            ProductDao productDao = new ProductDaoImpl(connection);

            OrderDao orderDao = new OrderDaoImpl(connection);
            OrderDetailDao orderDetailDao = new OrderDetailDaoImpl(connection);
            order.setUserId(user.getId());
            order.setLoginName(user.getLoginName());
            order.setUserAddress(address);
            order.setCreateTime(new Date());
            order.setCost(cart.getTotalCost());
            order.setSerialNumber(StringUtils.randomUUID());
            orderDao.add(order);

            for (ShoppingCartItem item : cart.getItems()) {
                OrderDetail orderDetail = new OrderDetail();
                orderDetail.setOrderId(order.getId());
                orderDetail.setCost(item.getCost());
                orderDetail.setProduct(item.getProduct());
                orderDetail.setQuantity(item.getQuantity());
                orderDetailDao.add(orderDetail);
                productDao.updateStock(item.getProduct().getId(), item.getQuantity());
                connection.commit();
            }
        } catch (Exception e) {
            e.printStackTrace();

            try {
                connection.rollback();
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        } finally {
            try {
                connection.setAutoCommit(true);
            } catch (SQLException e) {
                e.printStackTrace();
            }
            DataSourceUtil.closeConnection(connection);
        }
        return order;

    }

    @Override
    public List<Order> getOrderList(Integer userId, Integer currentPageNo, Integer pageSize) {
        Connection connection = null;

        List<Order> orderList = new ArrayList<Order>();

        try {
            connection = DataSourceUtil.openConnection();

            OrderDao jibai = new OrderDaoImpl(connection);

            OrderDetailDao jibaidao = new OrderDetailDaoImpl(connection);

            orderList = jibai.getOrderList(userId, currentPageNo, pageSize);

            for (Order order : orderList) {
                order.setOrderDetailList(jibaidao.getOrderDetail(order.getId()));
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }

        return orderList;
    }

    @Override
    public Integer count(Integer userId) {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();

            OrderDao jibai = new OrderDaoImpl(connection);

            OrderDetailDao jibaidao = new OrderDetailDaoImpl(connection);

            cc = jibai.count(userId);

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }

        return cc;
    }

    @Override
    public List<OrderDetail> getOrderDetailList(Integer orderId) {
        Connection connection = null;

        List<OrderDetail> orderDetailList = new ArrayList<OrderDetail>();

        try {
            connection = DataSourceUtil.openConnection();


            OrderDetailDao jibaidao = new OrderDetailDaoImpl(connection);

            orderDetailList = jibaidao.getOrderDetail(orderId);

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }

        return orderDetailList;
    }
}
