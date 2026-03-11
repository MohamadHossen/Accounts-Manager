#📁 Accounts Manager System

برنامج بسيط مكتوب بلغة C++ لإدارة الحسابات المختلفة (Gmail – Facebook – WhatsApp – Network) مع حفظ البيانات داخل ملف نصي.

---

##✨ الميزات الأساسية
- ➕ إضافة حساب جديد
- ❌ حذف حساب
- ✏️ تعديل بيانات حساب
- 🔍 البحث عن حساب
- 📋 عرض جميع الحسابات المخزنة

---

##📌 أنواع الحسابات المدعومة
- Gmail  
- Facebook  
- WhatsApp  
- Network  

---

##🧩 طريقة تخزين البيانات
يتم حفظ كل حساب داخل ملف  
Acounts.txt  
على شكل سطر واحد يحتوي على:
`
Type||UserName||Password
`

---

##🎯 طريقة الاستخدام
1. شغّل البرنامج.
2. اختر العملية التي تريد تنفيذها من القائمة (إضافة – حذف – تعديل – بحث – عرض).
3. أدخل البيانات المطلوبة حسب العملية.
4. سيتم حفظ التغييرات تلقائيًا داخل ملف Acounts.txt.

---

## 💻 مثال تشغيل (Console)
`
What Do You Want To Do ?
1 : Add Account
2 : Delete Account
3 : Change Account
4 : Search Account
5 : Show Accounts

I Want (Enter Number) : 1

What Type Of Account Do You Want ?
1 : Gmail
2 : FaceBook
3 : WhatsApp
4 : NetWork
Enter Number Of Your Choice : 1

Please Enter UserName :
Please Enter PassWord :

Do You Want To Do Anything Else ? Y/N ?
`

---

## 📝 ملاحظات
- الكود مناسب للتعلم على التعامل مع الملفات والدوال في C++.
- يمكنك تطوير المشروع لاحقًا لإضافة ميزات مثل:
  - تشفير كلمات المرور  
  - واجهة رسومية  
  - نظام تسجيل دخول  

---