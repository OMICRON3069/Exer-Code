package com.easybuy.web.pre;

import com.easybuy.biz.NewsBiz;
import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.biz.impl.NewsBizImpl;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.biz.impl.ProductCategoryBizImpl;
import com.easybuy.entity.News;
import com.easybuy.param.NewsParams;
import com.easybuy.util.Pager;
import com.easybuy.util.ProductCategoryVo;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;


@WebServlet(urlPatterns = {"/Home"}, name = "Home")
public class HomeServlet extends AbstractServlet {

    private ProductBiz productBiz;
    private NewsBiz newsBiz;
    private ProductCategoryBiz productCategoryBiz;

    @Override
    public void init() throws ServletException {
        productBiz = new ProductBizImpl();
        newsBiz = new NewsBizImpl();
        productCategoryBiz = new ProductCategoryBizImpl();
    }

    @Override
    public Class getServletClass() {


        return HomeServlet.class;
    }

    public String index(HttpServletRequest request, HttpServletResponse response) throws Exception {

        List<ProductCategoryVo> productCategoryVoList = productCategoryBiz.AllProductCategoryList();

        Pager pager = new Pager(5, 5, 1);
        NewsParams params = new NewsParams();
        params.openPage((pager.getCurrentPage()-1)*pager.getRowPerpage(),pager.getRowPerpage());

        List<News> news = newsBiz.queryNewsList(params);

        for (ProductCategoryVo vo: productCategoryVoList) {
            productBiz.getProductList(1,8,null,vo.getProductCategory().getId(),1);

        }
        return "/pre/index";
    }
}
