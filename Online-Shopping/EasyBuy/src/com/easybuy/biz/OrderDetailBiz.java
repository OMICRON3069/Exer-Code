package com.easybuy.biz;

import com.easybuy.entity.OrderDetail;

import java.util.List;

public interface OrderDetailBiz {
    void add (OrderDetail detail);

    void deleteById(OrderDetail detail);
    Integer count();
    OrderDetail getOrderDetailById(Integer id);
    List<OrderDetail> getOrderDetail(Integer orderId);
}
