package com.easybuy.dao;

import com.easybuy.entity.Order;

import java.util.List;

public interface OrderDao {

    void add (Order order);

    void deleteById (Integer id);

    Order getOrderById(Integer id);

    Integer count (Integer userId);

    /**
     * get user order list
     * @param userId user id
     * @param currentPageNo current page number
     * @param pageSize row per page
     *
     */
    List<Order> getOrderList(Integer userId, Integer currentPageNo, Integer pageSize);

}
