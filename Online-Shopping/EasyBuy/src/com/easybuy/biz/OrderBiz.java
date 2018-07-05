package com.easybuy.biz;

import com.easybuy.entity.Order;

import java.util.List;

public interface OrderBiz {
    void add (Order order);

    void deleteById (Integer id);

    Order getOrderById(Integer id);

    Integer count (Integer userId);

    List<Order> getOrderList(Integer userId, Integer currentPageNo, Integer pageSize);
}
