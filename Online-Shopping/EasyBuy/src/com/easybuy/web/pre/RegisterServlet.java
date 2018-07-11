package com.easybuy.web.pre;

import com.easybuy.biz.UserBiz;
import com.easybuy.biz.impl.UserBizImpl;
import com.easybuy.entity.User;
import com.easybuy.util.Constants;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.ReturnResult;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns = {"/Register"}, name = "Register")

public class RegisterServlet extends AbstractServlet {

    private UserBiz userBiz;

    @Override
    public void init() throws ServletException {
        userBiz = new UserBizImpl();

    }

    @Override
    public Class getServletClass() {
        return RegisterServlet.class;
    }

    public String toRegister(HttpServletRequest request, HttpServletResponse response) throws Exception {
        return "/pre/register";
    }

    public ReturnResult saveUserToDatabase(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();

        User user = new User();

        String loginName = request.getParameter("loginName");
        User oldUser = userBiz.getUser(null, loginName);
        if (EmptyUtils.isNotEmpty(oldUser)) {
            result.returnFail("User exist");
            return result;
        }


        try {
            user.setLoginName(loginName);
            user.setUserName(request.getParameter("userName"));
            user.setSex(EmptyUtils.isEmpty(request.getParameter("sex")) ? 1 : 0);
            user.setPassword(request.getParameter("password"));
            user.setIdentityCode(request.getParameter("identityCode"));
            user.setEmail(request.getParameter("email"));
            user.setMobile(request.getParameter("mobile"));
            user.setType(Constants.UserType.PRE);

            result = checkUser(user);
            if (result.getStatus() == Constants.ReturnResult.SUCCESS) {
                if (!userBiz.add(user)) {
                    return result.returnFail("Register fail");
                }
            }

            result.returnSuccess("welcome!");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return result;
    }

    private ReturnResult checkUser(User user) {
        ReturnResult result = new ReturnResult();
        //TODO: More check
        return result.returnSuccess();
    }
}
