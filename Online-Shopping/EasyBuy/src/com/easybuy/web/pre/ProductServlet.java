package com.easybuy.web.pre;

import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.biz.impl.ProductCategoryBizImpl;
import com.easybuy.entity.Product;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;
import com.easybuy.util.ProductCategoryVo;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

@WebServlet(urlPatterns = {"/Product"}, name = "Product")

public class ProductServlet extends AbstractServlet {

    private ProductBiz productBiz;

    private ProductCategoryBiz productCategoryBiz;

    @Override
    public void init() throws ServletException {
        productBiz = new ProductBizImpl();
        productCategoryBiz = new ProductCategoryBizImpl();
    }

    @Override
    public Class getServletClass() {
        return ProductCategoryServlet.class;
    }


    private void addRecentProduct(HttpServletRequest request, Product product) throws Exception {
        HttpSession session = request.getSession();
        List<Product> recentProducts = queryRecentProduct(request);


        if (recentProducts.size() > 0 && recentProducts.size() >= 10) {
            recentProducts.remove(0);
        }

        recentProducts.add(recentProducts.size(), product);
        session.setAttribute("recentProducts", recentProducts);
    }

    private List<Product> queryRecentProduct(HttpServletRequest request) {
        HttpSession session = request.getSession();
        List<Product> recentProducts = (List<Product>) session.getAttribute("recentProducts");

        if (EmptyUtils.isEmpty(recentProducts)) {
            recentProducts = new ArrayList<Product>();
        }
        return recentProducts;
    }

    public String queryProductList(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String category = request.getParameter("category");
        String levelStr = request.getParameter("level");
        String currentPageStr = request.getParameter("currentPage");
        String keyWord = request.getParameter("keyWord");
        String pageSizeStr = request.getParameter("pageSize");

        int rowPerPage = EmptyUtils.isEmpty(pageSizeStr) ? 20 : Integer.parseInt(pageSizeStr);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        int level = EmptyUtils.isEmpty(levelStr) ? 0 : Integer.parseInt(levelStr);

        Integer categoryId = EmptyUtils.isEmpty(category) ? null : Integer.valueOf(category);

        int total = productBiz.queryProductCount(keyWord, categoryId, level);
        Pager pager = new Pager(total, rowPerPage, currentPage);


        pager.setUrl("/Product?action=queryProductList&level=" + level + "&category=" + (EmptyUtils.isEmpty(category) ? "" : category));

        List<ProductCategoryVo> productCategoryVoList = productCategoryBiz.AllProductCategoryList();
        List<Product> productList = productBiz.getProductList(currentPage, rowPerPage, keyWord, categoryId, level);
        request.setAttribute("productList", productList);
        request.setAttribute("pager", pager);
        request.setAttribute("total", total);
        request.setAttribute("keyWord", keyWord);
        request.setAttribute("productCategoryVoList", productCategoryVoList);

        return "/pre/product/queryProductList";
    }

    public String queryProductDetail(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        Product product = productBiz.getProductById(Integer.valueOf(id));
        List<ProductCategoryVo> productCategoryVoList = productCategoryBiz.AllProductCategoryList();
        request.setAttribute("product",product);
        request.setAttribute("productCategoryVoList",productCategoryVoList);
        addRecentProduct(request,product);
        return "/pre/product/productDetail";
    }


}
