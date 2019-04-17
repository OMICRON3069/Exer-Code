package com.easybuy.web.pre;


import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.entity.Product;
import com.easybuy.entity.User;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.MemcachedUtils;
import com.easybuy.util.ReturnResult;
import com.easybuy.web.AbstractServlet;

/**
 */
@WebServlet(urlPatterns = {"/Favorite"}, name = "Favorite")
public class FavoriteServlet extends AbstractServlet {


    private ProductBiz productBiz;

    public void init() throws ServletException {
        productBiz = new ProductBizImpl();
    }

    @Override
    public Class getServletClass() {
        return FavoriteServlet.class;
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String toFavoriteList(HttpServletRequest request, HttpServletResponse response) throws Exception {
        List<Product> recentProducts = queryFavoriteList(request);
        request.setAttribute("recentProducts", recentProducts);
        return "/pre/product/favoriteList";
    }

    /**
     * @return
     */
    public ReturnResult addFavorite(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        String id = request.getParameter("id");
        Product product = productBiz.getProductById(Integer.valueOf(id));
        List<Product> favoriteList = queryFavoriteList(request);
        if (favoriteList.size() > 0 && favoriteList.size() == 5) {
            favoriteList.remove(0);
        }
        boolean temp = false;
        for (int i = 0; i < favoriteList.size(); i++) {
            if (favoriteList.get(i).getId().equals(product.getId())) {
                temp = true;
                break;
            }
        }
        if (!temp) {
            favoriteList.add(favoriteList.size(), product);
        }
        MemcachedUtils.add(getFavoriteKey(request), favoriteList);
        result.returnSuccess();
        return result;
    }

    /**
     * @return
     */
    private List<Product> queryFavoriteList(HttpServletRequest request) throws Exception {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("loginUser");
        String key = EmptyUtils.isEmpty(user) ? session.getId() : user.getLoginName();
        List<Product> recentProducts = (List<Product>) MemcachedUtils.get(key);
        if (EmptyUtils.isEmpty(recentProducts)) {
            recentProducts = new ArrayList<Product>();
        }
        return recentProducts;
    }

    /**
     * @param request
     * @return
     */
    private String getFavoriteKey(HttpServletRequest request) throws Exception {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("loginUser");
        return EmptyUtils.isEmpty(user) ? session.getId() : user.getLoginName();
    }
}
