package com.easybuy.web.backend;


import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.easybuy.biz.UserBiz;
import com.easybuy.biz.impl.UserBizImpl;
import com.easybuy.entity.User;
import com.easybuy.util.Constants;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;
import com.easybuy.util.ReturnResult;
import com.easybuy.web.AbstractServlet;

/**
 */
@WebServlet(urlPatterns = {"/admin/user"}, name = "adminUser")
public class AdminUserServlet extends AbstractServlet {

    private UserBiz userBiz;

    public void init() throws ServletException {
        userBiz = new UserBizImpl();
    }

    @Override
    public Class getServletClass() {
        return AdminUserServlet.class;
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String index(HttpServletRequest request, HttpServletResponse response) throws Exception {
        User user = (User) request.getSession().getAttribute("loginUser");
        request.setAttribute("user", user);
        request.setAttribute("menu", 2);
        return "/backend/user/userInfo";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String queryUserList(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String currentPageStr = request.getParameter("currentPage");
        String pageSize = request.getParameter("pageSize");
        int rowPerPage = EmptyUtils.isEmpty(pageSize) ? 10 : Integer.parseInt(pageSize);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        int total = userBiz.count();
        Pager pager = new Pager(total, rowPerPage, currentPage);
        List<User> userList = userBiz.getUserList(currentPage, rowPerPage);
        pager.setUrl("/admin/user?action=queryUserList");
        request.setAttribute("userList", userList);
        request.setAttribute("pager", pager);
        request.setAttribute("menu", 8);
        return "/backend/user/userList";
    }

    /**
     * 修改用户信息
     *
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public String toUpdateUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        User user = userBiz.getUser(Integer.parseInt(id), null);
        request.setAttribute("user", user);
        return "/backend/user/toUpdateUser";
    }

    /**
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public String toAddUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
        User user = new User();
        request.setAttribute("user", user);
        return "/backend/user/toUpdateUser";
    }

    /**
     * 更新用户
     *
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ReturnResult updateUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        String id = request.getParameter("id");
        User user = new User();
        String loginName = request.getParameter("loginName");
        String sex = request.getParameter("sex");
        User oldUser = userBiz.getUser(null, loginName);

        if (EmptyUtils.isNotEmpty(oldUser) && (EmptyUtils.isEmpty(id) || oldUser.getId() != Integer.parseInt(id))) {
            result.returnFail("�û��Ѵ���");
            return result;
        }
        user.setLoginName(loginName);
        user.setUserName(request.getParameter("userName"));
        user.setSex(EmptyUtils.isEmpty(sex) ? 1 : 0);
        if (EmptyUtils.isEmpty(id) || id.equals("0")) {
            user.setPassword(request.getParameter("password"));
        }
        user.setIdentityCode(request.getParameter("identityCode"));
        user.setEmail(request.getParameter("email"));
        user.setMobile(request.getParameter("mobile"));
        user.setType(Integer.parseInt(request.getParameter("type")));

        result = checkUser(user);
        if (result.getStatus() == Constants.ReturnResult.SUCCESS) {
            if (EmptyUtils.isEmpty(id) || id.equals("0")) {
                if (!userBiz.add(user)) {
                    return result.returnFail("����ʧ��");
                }
            } else {
                user.setId(Integer.parseInt(id));
                if (!userBiz.update(user)) {
                    return result.returnFail("�޸�ʧ��");
                }
            }
        }
        result.returnSuccess();
        return result;


    }

    public ReturnResult deleteUserById(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        String id = request.getParameter("id");
        userBiz.deleteUserById(Integer.parseInt(id));
        result.returnSuccess();
        return result;
    }

    private ReturnResult checkUser(User user) {
        ReturnResult result = new ReturnResult();
        /*
         * ��Ϣ��֤
         */
        return result.returnSuccess();
    }

}
