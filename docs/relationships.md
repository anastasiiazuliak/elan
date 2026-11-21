# Relationships

| Entities | Cardinality | Implementation |
| --- | --- | --- |
| Person → Admin, Client, Employee, Coach | Inheritance | Each role has a separate account store. |
| Location → Employee | One to many | An employee can reference one work location. |
| Location → Hall | One to many | Each location owns up to five halls. Hall IDs are local to the location. |
| Location → Schedule | One to many | Each location owns the weekly slots for its halls. |
| Hall → Schedule | One to many | Each occupied slot references one hall within its location. |
| Group → Schedule | One to many | A group can appear in several weekly slots. Each occupied slot references one group. |
| Coach → Group | One to many | Each group references one coach. A coach can lead several groups. |
| Style → Group | One to many | Each group references one style. A style can be used by several groups. |
| Coach ↔ Style | Many to many | Each coach can list several styles, and several coaches can teach the same style. |
| Group ↔ Subscription | Many to many | A group lists its allowed plans. A plan can be offered in several groups. |
| Client ↔ Group | Many to many via Membership | A membership links one client to one group. The service allows one active membership per client and group pair. |
| Subscription → Membership | One to many | Each membership references the plan used for its duration and visit allowance. |

The [editable relationship diagram](relationship.drawio) shows the same domain model.