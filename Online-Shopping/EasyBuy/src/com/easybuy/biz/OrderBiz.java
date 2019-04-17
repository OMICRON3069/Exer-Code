package com.easybuy.biz;

import com.easybuy.entity.Order;
import com.easybuy.entity.OrderDetail;
import com.easybuy.entity.User;
import com.easybuy.util.ShoppingCart;

import java.util.List;

public interface OrderBiz {

    Order payShoppingCart(ShoppingCart cart, User user, String address);

    List<Order> getOrderList(Integer userId, Integer currentPageNo, Integer pageSize);

    Integer count(Integer userId);

    List<OrderDetail> getOrderDetailList(Integer orderId);


}
