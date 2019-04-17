package com.easybuy.util;

import com.easybuy.entity.Product;

import java.io.Serializable;

public class ShoppingCartItem implements Serializable {

    private Product product;

    private Integer quantity;

    private float cost;


    public ShoppingCartItem(Product product, Integer quantity) {
        this.product = product;
        this.quantity = quantity;
        this.cost = product.getPrice()*quantity;
    }

    public Product getProduct() {
        return product;
    }

    public void setProduct(Product product) {
        this.product = product;
    }

    public Integer getQuantity() {
        return quantity;
    }

    public void setQuantity(Integer quantity) {
        this.cost = product.getPrice()*quantity;
        this.quantity = quantity;
    }

    public float getCost() {
        return cost;
    }

    public void setCost(float cost) {
        this.cost = cost;
    }
}
