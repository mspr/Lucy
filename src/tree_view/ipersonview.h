#ifndef IPERSONVIEW_H
#define IPERSONVIEW_H

class IPersonViewModel;

class IPersonView
{
  public:
    IPersonView();

    void setModel(IPersonViewModel* model);
    IPersonViewModel* model() const;

  private:
    IPersonViewModel* _model;
};

#endif // IPERSONVIEW_H
