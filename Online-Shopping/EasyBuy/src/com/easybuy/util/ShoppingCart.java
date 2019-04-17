package com.easybuy.util;

import com.easybuy.entity.Product;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class ShoppingCart implements Serializable {

    List<ShoppingCartItem> items = new ArrayList<ShoppingCartItem>();

    private Double sum;


    public ReturnResult addItem(Product product, Integer quantity) {
        ReturnResult result = new ReturnResult();

        int flag = 0;

        for (int i = 0; i < items.size(); i++) {

            if ((items.get(i).getProduct().getId()).equals(product.getId())) {
                if (items.get(i).getQuantity() + quantity > product.getStock()) {
                    return result.returnFail("out of stock");
                } else {
                    items.get(i).setQuantity(items.get(i).getQuantity() + quantity);
                    flag = 1;
                }
            }

        }

        if (quantity > product.getStock()) {
            return result.returnFail("out of stock");
        }
        if (flag == 0) {
            items.add(new ShoppingCartItem(product, quantity));
        }
        return result.returnSuccess();
    }


    public void removeItem(Integer index) {
        items.remove(index);
    }

    public void modifyQuantity(Integer index, Integer quantity) {
        items.get(index).setQuantity(quantity);
    }

    public float getTotalCost() {
        float sum = 0;
        for (ShoppingCartItem item : items) {
            sum += item.getCost();
        }
        return sum;
    }

    public List<ShoppingCartItem> getItems() {
        return items;
    }

    public void setItems(List<ShoppingCartItem> items) {
        this.items = items;
    }

    public Double getSum() {
        return sum;
    }

    public void setSum(Double sum) {
        this.sum = sum;
    }
}
