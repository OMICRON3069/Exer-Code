package com.easybuy.web.pre;


import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.easybuy.biz.CartBiz;
import com.easybuy.biz.OrderBiz;
import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.biz.UserAddressBiz;
import com.easybuy.biz.UserBiz;
import com.easybuy.biz.impl.CartBizImpl;
import com.easybuy.biz.impl.OrderBizImpl;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.biz.impl.ProductCategoryBizImpl;
import com.easybuy.biz.impl.UserAddressBizImpl;
import com.easybuy.biz.impl.UserBizImpl;
import com.easybuy.entity.Order;
import com.easybuy.entity.Product;
import com.easybuy.entity.User;
import com.easybuy.entity.UserAddress;
import com.easybuy.util.Constants;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.ProductCategoryVo;
import com.easybuy.util.ReturnResult;
import com.easybuy.util.ShoppingCart;
import com.easybuy.util.ShoppingCartItem;
import com.easybuy.web.AbstractServlet;

/**
 */
@WebServlet(urlPatterns = {"/Cart"}, name = "Cart")
public class CartServlet extends AbstractServlet {

    private ProductBiz productBiz;

    private OrderBiz orderBiz;

    private UserBiz userBiz;

    private ProductCategoryBiz productCategoryBiz;

    private CartBiz cartBiz;

    private UserAddressBiz userAddressBiz;

    public void init() throws ServletException {
        productBiz = new ProductBizImpl();
        orderBiz = new OrderBizImpl();
        userBiz = new UserBizImpl();
        productCategoryBiz = new ProductCategoryBizImpl();
        cartBiz = new CartBizImpl();
        userAddressBiz = new UserAddressBizImpl();
    }

    @Override
    public Class getServletClass() {
        return CartServlet.class;
    }

    /**
     * @return
     */
    public ReturnResult add(HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        ReturnResult result = new ReturnResult();
        String id = request.getParameter("entityId");
        String quantityStr = request.getParameter("quantity");
        Integer quantity = 1;
        if (!EmptyUtils.isEmpty(quantityStr))
            quantity = Integer.parseInt(quantityStr);
        Product product = productBiz.getProductById(Integer.valueOf(id));
        if (product.getStock() < quantity) {
            return result.returnFail("��Ʒ��������");
        }
        ShoppingCart cart = getCartFromSession(request);
        result = cart.addItem(product, quantity);
        if (result.getStatus() == Constants.ReturnResult.SUCCESS) {
            cart.setSum((EmptyUtils.isEmpty(cart.getSum()) ? 0.0 : cart.getSum()) + (product.getPrice() * quantity * 1.0));
        }
        return result;
    }


    /**
     * @param request
     * @param response
     * @return
     */
    public String refreshCart(HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        ShoppingCart cart = getCartFromSession(request);
        cart = cartBiz.calculate(cart);
        session.setAttribute("cart", cart);
        return "/common/pre/searchBar";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String toSettlement(HttpServletRequest request, HttpServletResponse response) throws Exception {
        List<ProductCategoryVo> productCategoryVoList = productCategoryBiz.AllProductCategoryList();
        request.setAttribute("productCategoryVoList", productCategoryVoList);
        return "/pre/settlement/toSettlement";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String settlement1(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ShoppingCart cart = getCartFromSession(request);
        cart = cartBiz.calculate(cart);
        request.getSession().setAttribute("cart", cart);
        return "/pre/settlement/settlement1";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String settlement2(HttpServletRequest request, HttpServletResponse response) throws Exception {
        User user = getUserFromSession(request);
        List<UserAddress> userAddressList = userAddressBiz.queryUserAddressList(user.getId());
        request.setAttribute("userAddressList", userAddressList);
        return "/pre/settlement/settlement2";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public Object settlement3(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ShoppingCart cart = getCartFromSession(request);
        cart = cartBiz.calculate(cart);
        User user = getUserFromSession(request);
        ReturnResult result = checkCart(request);
        if (result.getStatus() == Constants.ReturnResult.FAIL) {
            return result;
        }
        String addressId = request.getParameter("addressId");
        String newAddress = request.getParameter("newAddress");
        String newRemark = request.getParameter("newRemark");
        UserAddress userAddress = new UserAddress();
        if (addressId.equals("-1")) {
            userAddress.setRemark(newRemark);
            userAddress.setAddress(newAddress);
            userAddress.setId(userAddressBiz.addUserAddress(user.getId(), newAddress, newRemark));
        } else {
            userAddress = userAddressBiz.getUserAddressById(Integer.parseInt(addressId));
        }

        Order order = orderBiz.payShoppingCart(cart, user, userAddress.getAddress());
        clearCart(request, response);
        request.setAttribute("currentOrder", order);
        return "/pre/settlement/settlement3";
    }

    /**
     * @param request
     * @param response
     */
    public ReturnResult clearCart(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        request.getSession().removeAttribute("cart");
        result.returnSuccess(null);
        return result;
    }

    /**
     * @param request
     * @return
     */
    public ReturnResult modCart(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        HttpSession session = request.getSession();
        String id = request.getParameter("entityId");
        String quantityStr = request.getParameter("quantity");
        ShoppingCart cart = getCartFromSession(request);
        Product product = productBiz.getProductById(Integer.valueOf(id));
        if (EmptyUtils.isNotEmpty(quantityStr)) {
            if (Integer.parseInt(quantityStr) > product.getStock()) {
                return result.returnFail("��Ʒ��������");
            }
        }
        cart = cartBiz.modifyShoppingCart(id, quantityStr, cart);
        session.setAttribute("cart", cart);
        return result.returnSuccess();
    }

    /**
     * @param request
     * @return
     */
    private ShoppingCart getCartFromSession(HttpServletRequest request) throws Exception {
        HttpSession session = request.getSession();
        ShoppingCart cart = (ShoppingCart) session.getAttribute("cart");
        if (cart == null) {
            cart = new ShoppingCart();
            session.setAttribute("cart", cart);
        }
        return cart;
    }

    private ReturnResult checkCart(HttpServletRequest request) throws Exception {
        ReturnResult result = new ReturnResult();
        HttpSession session = request.getSession();
        ShoppingCart cart = getCartFromSession(request);
        cart = cartBiz.calculate(cart);
        for (ShoppingCartItem item : cart.getItems()) {
            Product product = productBiz.getProductById(item.getProduct().getId());
            if (product.getStock() < item.getQuantity()) {
                return result.returnFail(product.getName() + "��Ʒ��������");
            }
        }
        return result.returnSuccess();
    }

    /**
     * @param request
     * @return
     */
    private User getUserFromSession(HttpServletRequest request) {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("loginUser");
        return user;
    }
}
