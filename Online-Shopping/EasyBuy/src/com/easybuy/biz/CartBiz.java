package com.easybuy.biz;

import com.easybuy.util.ShoppingCart;


public interface CartBiz {

    public ShoppingCart modifyShoppingCart(String productId, String quantityStr, ShoppingCart cart) throws Exception;

    public ShoppingCart calculate(ShoppingCart cart) throws Exception;
}
