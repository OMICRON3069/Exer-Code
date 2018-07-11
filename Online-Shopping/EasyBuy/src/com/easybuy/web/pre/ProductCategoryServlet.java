package com.easybuy.web.pre;

import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.biz.impl.ProductCategoryBizImpl;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(urlPatterns = {"/productCategory"},name = "productCategoryServlet")
public class ProductCategoryServlet extends AbstractServlet {

    private ProductCategoryBiz productCategoryBiz;
    @Override
    public Class getServletClass() {
        return ProductCategoryServlet.class;
    }

    @Override
    public void init() throws ServletException {
        productCategoryBiz = new ProductCategoryBizImpl();
    }
}
