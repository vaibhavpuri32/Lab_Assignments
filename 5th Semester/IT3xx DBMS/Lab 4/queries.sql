SELECT pa.Name, ph.Name FROM Patient pa, PhysicianE ph WHERE pa.Pcp = ph.EmployeeID and ph.EmployeeID NOT IN (SELECT Head FROM Department);

SELECT pa.Name FROM Patient pa, Appointment ap, Nurse nu WHERE pa.Ssn = ap.Patient AND ap.Prepnurse = nu.EmployeeID AND nu.registered = 1 AND pa.Pcp = ap.Physician GROUP BY pa.Name HAVING (COUNT(*) > 1);

SELECT pa.Name FROM Patient pa, Procedures pr, Undergoes un WHERE pa.Ssn = un.Patient AND un.Procedures = pr.Code AND pr.Cost > 5000 AND pa.Pcp = un.Physician;

SELECT ph.Name AS Physician, ph.Position, pr.Name AS 'Procedure Name', un.DateUndergoes AS 'Date Of Procedure', pa.Name AS Patient FROM PhysicianE ph, Procedures pr, Undergoes un, Patient pa, Trained_In tr WHERE un.DateUndergoes > tr.CertificationExpires AND ph.EmployeeID = un.Physician AND ph.EmployeeID = tr.Physician AND un.Procedures = pr.Code AND un.Patient = pa.Ssn;

SELECT ph.Name FROM PhysicianE ph, Undergoes un, Trained_In ti WHERE ph.EmployeeID = un.Physician AND ph.EmployeeID = ti.Physician AND un.DateUndergoes > ti.CertificationExpires;