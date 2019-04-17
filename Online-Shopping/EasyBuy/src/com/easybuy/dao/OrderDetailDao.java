package com.easybuy.dao;

import com.easybuy.entity.OrderDetail;
import com.easybuy.param.OrderDetailParam;

import java.util.List;

public interface OrderDetailDao {
    void add (OrderDetail detail);

    void deleteById(OrderDetail detail);
    Integer count();
    OrderDetail getOrderDetailById(Integer id);
    List<OrderDetail> getOrderDetail(Integer orderId);
}
